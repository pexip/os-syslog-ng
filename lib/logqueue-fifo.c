/*
 * Copyright (c) 2002-2010 BalaBit IT Ltd, Budapest, Hungary
 * Copyright (c) 1998-2010 Balázs Scheidler
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */

#include "logqueue.h"
#include "logpipe.h"
#include "messages.h"
#include "serialize.h"
#include "stats.h"
#include "mainloop.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <iv_thread.h>

/*
 * LogFifo is a scalable first-in-first-output queue implementation, that:
 *
 *   - has a per-thread, unlocked input queue where threads can put their items
 *
 *   - has a locked wait-queue where items go once the per-thread input
 *     would be overflown or if the input thread goes to sleep (e.g.  one
 *     lock acquisition per a longer period)
 *
 *   - has an unlocked output queue where items from the wait queue go, once
 *     it becomes depleted.
 *
 * This means that items flow in this sequence from one list to the next:
 *
 *    input queue (per-thread) -> wait queue (locked) -> output queue (single-threaded)
 *
 * Fastpath is:
 *   - input threads putting elements on their per-thread queue (lockless)
 *   - output threads removing elements from the output queue (lockless)
 *
 * Slowpath:
 *   - input queue is overflown (or the input thread goes to sleep), wait
 *     queue mutex is grabbed, all elements are put to the wait queue.
 *
 *   - output queue is depleted, wait queue mutex is grabbed, all elements
 *     on the wait queue is put to the output queue
 *
 * Threading assumptions:
 *   - the head of the queue is only manipulated from the output thread
 *   - the tail of the queue is only manipulated from the input threads
 *
 */


typedef struct _LogQueueFifo
{
  LogQueue super;
  
  /* scalable qoverflow implementation */
  struct list_head qoverflow_output;
  struct list_head qoverflow_wait;
  gint qoverflow_wait_len;
  gint qoverflow_output_len;
  gint qoverflow_size; /* in number of elements */

  struct list_head qbacklog;    /* entries that were sent but not acked yet */
  gint qbacklog_len;

  struct
  {
    struct list_head items;
    MainLoopIOWorkerFinishCallback cb;
    guint16 len;
    guint16 finish_cb_registered;
  } qoverflow_input[0];
} LogQueueFifo;

/* NOTE: this is inherently racy. If the LogQueue->lock is taken, then the
 * race is limited to the changes in qoverflow_output queue changes.
 *
 * In the output thread, this means that this can get race-free. In the
 * input thread, the qoverflow_output can change because of a
 * log_queue_fifo_push_head() or log_queue_fifo_rewind_backlog().
 *
 */
static gint64
log_queue_fifo_get_length(LogQueue *s)
{
  LogQueueFifo *self = (LogQueueFifo *) s;

  return self->qoverflow_wait_len + self->qoverflow_output_len;
}

/* NOTE: this is inherently racy, can only be called if log processing is suspended (e.g. reload time) */
static gboolean
log_queue_fifo_keep_on_reload(LogQueue *s)
{
  return log_queue_fifo_get_length(s) > 0;
}

/* move items from the per-thread input queue to the lock-protected "wait" queue */
static void
log_queue_fifo_move_input_unlocked(LogQueueFifo *self, gint thread_id)
{
  gint queue_len;

  /* since we're in the input thread, queue_len will be racy. It can
   * increase due to log_queue_fifo_push_head() and can also decrease as
   * items are removed from the output queue using log_queue_pop_head().
   *
   * The only reason we're using it here is to check for qoverflow
   * overflows, however the only side-effect of the race (if lost) is that
   * we would lose a couple of message too many or add some more messages to
   * qoverflow than permitted by the user.  Since if flow-control is used,
   * the fifo size should be sized larger than the potential window sizes,
   * otherwise we can lose messages anyway, this is not deemed a cost to
   * justify proper locking in this case.
   */

  queue_len = log_queue_fifo_get_length(&self->super);
  if (queue_len + self->qoverflow_input[thread_id].len > self->qoverflow_size)
    {
      /* slow path, the input thread's queue would overflow the queue, let's drop some messages */

      LogPathOptions path_options = LOG_PATH_OPTIONS_INIT;
      gint i;
      gint n;

      /* NOTE: MAX is needed here to ensure that the lost race on queue_len
       * doesn't result in n < 0 */
      n = self->qoverflow_input[thread_id].len - MAX(0, (self->qoverflow_size - queue_len));

      for (i = 0; i < n; i++)
        {
          LogMessageQueueNode *node = list_entry(self->qoverflow_input[thread_id].items.next, LogMessageQueueNode, list);
          LogMessage *msg = node->msg;

          list_del(&node->list);
          self->qoverflow_input[thread_id].len--;
          path_options.ack_needed = node->ack_needed;
          stats_counter_inc(self->super.dropped_messages);
          log_msg_free_queue_node(node);
          log_msg_drop(msg, &path_options);
        }
      msg_debug("Destination queue full, dropping messages",
                evt_tag_int("queue_len", queue_len),
                evt_tag_int("log_fifo_size", self->qoverflow_size),
                evt_tag_int("count", n),
                NULL);
    }
  stats_counter_add(self->super.stored_messages, self->qoverflow_input[thread_id].len);
  list_splice_tail_init(&self->qoverflow_input[thread_id].items, &self->qoverflow_wait);
  self->qoverflow_wait_len += self->qoverflow_input[thread_id].len;
  self->qoverflow_input[thread_id].len = 0;
}

/* move items from the per-thread input queue to the lock-protected
 * "wait" queue, but grabbing locks first. This is registered as a
 * callback to be called when the input worker thread finishes its
 * job.
 */
static gpointer
log_queue_fifo_move_input(gpointer user_data)
{
  LogQueueFifo *self = (LogQueueFifo *) user_data;
  gint thread_id;

  thread_id = main_loop_io_worker_thread_id();

  g_assert(thread_id >= 0);

  g_static_mutex_lock(&self->super.lock);
  log_queue_fifo_move_input_unlocked(self, thread_id);
  log_queue_push_notify(&self->super);
  g_static_mutex_unlock(&self->super.lock);
  self->qoverflow_input[thread_id].finish_cb_registered = FALSE;
  return NULL;
}

/**
 * Assumed to be called from one of the input threads. If the thread_id
 * cannot be determined, the item is put directly in the wait queue.
 *
 * Puts the message to the queue, and logs an error if it caused the
 * queue to be full.
 *
 * It attempts to put the item to the per-thread input queue.
 **/
static void
log_queue_fifo_push_tail(LogQueue *s, LogMessage *msg, const LogPathOptions *path_options)
{
  LogQueueFifo *self = (LogQueueFifo *) s;
  gint thread_id;
  LogMessageQueueNode *node;

  thread_id = main_loop_io_worker_thread_id();

  g_assert(thread_id < 0 || log_queue_max_threads > thread_id);

  /* NOTE: we don't use high-water marks for now, as log_fetch_limit
   * limits the number of items placed on the per-thread input queue
   * anyway, and any sane number decreased the performance measurably.
   *
   * This means that per-thread input queues contain _all_ items that
   * a single poll iteration produces. And once the reader is finished
   * (either because the input is depleted or because of
   * log_fetch_limit / window_size) the whole bunch is propagated to
   * the "wait" queue.
   */

  if (thread_id >= 0) {
      /* fastpath, use per-thread input FIFOs */
      if (!self->qoverflow_input[thread_id].finish_cb_registered)
        {
          /* this is the first item in the input FIFO, register a finish
           * callback to make sure it gets moved to the wait_queue if the
           * input thread finishes */

          main_loop_io_worker_register_finish_callback(&self->qoverflow_input[thread_id].cb);
          self->qoverflow_input[thread_id].finish_cb_registered = TRUE;
        }

      node = log_msg_alloc_queue_node(msg, path_options);
      list_add_tail(&node->list, &self->qoverflow_input[thread_id].items);
      self->qoverflow_input[thread_id].len++;
      log_msg_unref(msg);
      return;
    }

  /* slow path, put the pending item and the whole input queue to the wait_queue */

  g_static_mutex_lock(&self->super.lock);
  
  if (thread_id >= 0)
    log_queue_fifo_move_input_unlocked(self, thread_id);
  
  if (log_queue_fifo_get_length(s) < self->qoverflow_size)
    {
      node = log_msg_alloc_queue_node(msg, path_options);

      list_add_tail(&node->list, &self->qoverflow_wait);
      self->qoverflow_wait_len++;
      log_queue_push_notify(&self->super);

      stats_counter_inc(self->super.stored_messages);
      g_static_mutex_unlock(&self->super.lock);

      log_msg_unref(msg);
    }
  else
    {
      stats_counter_inc(self->super.dropped_messages);
      g_static_mutex_unlock(&self->super.lock);
      log_msg_drop(msg, path_options);

      msg_debug("Destination queue full, dropping message",
                evt_tag_int("queue_len", log_queue_fifo_get_length(&self->super)),
                evt_tag_int("log_fifo_size", self->qoverflow_size),
                NULL);
    }
  return;
}

/*
 * Put an item back to the front of the queue.
 *
 * This is assumed to be called only from the output thread.
 */
static void
log_queue_fifo_push_head(LogQueue *s, LogMessage *msg, const LogPathOptions *path_options)
{
  LogQueueFifo *self = (LogQueueFifo *) s;
  LogMessageQueueNode *node;

  /* we don't check limits when putting items "in-front", as it
   * normally happens when we start processing an item, but at the end
   * can't deliver it. No checks, no drops either. */

  log_queue_assert_output_thread(s);

  node = log_msg_alloc_dynamic_queue_node(msg, path_options);
  list_add(&node->list, &self->qoverflow_output);
  self->qoverflow_output_len++;

  stats_counter_inc(self->super.stored_messages);
}

/*
 * Can only run from the output thread.
 */
static gboolean
log_queue_fifo_pop_head(LogQueue *s, LogMessage **msg, LogPathOptions *path_options, gboolean push_to_backlog, gboolean ignore_throttle)
{
  LogQueueFifo *self = (LogQueueFifo *) s;
  LogMessageQueueNode *node;

  log_queue_assert_output_thread(s);

  if (!ignore_throttle && self->super.throttle && self->super.throttle_buckets == 0)
    {
      return FALSE;
    }
    
  if (self->qoverflow_output_len == 0)
    {
      /* slow path, output queue is empty, get some elements from the wait queue */
      g_static_mutex_lock(&self->super.lock);
      list_splice_tail_init(&self->qoverflow_wait, &self->qoverflow_output);
      self->qoverflow_output_len = self->qoverflow_wait_len;
      self->qoverflow_wait_len = 0;
      g_static_mutex_unlock(&self->super.lock);
    }

  if (self->qoverflow_output_len > 0)
    {
      node = list_entry(self->qoverflow_output.next, LogMessageQueueNode, list);

      *msg = node->msg;
      path_options->ack_needed = node->ack_needed;
      self->qoverflow_output_len--;
      if (!push_to_backlog)
        {
          list_del(&node->list);
          log_msg_free_queue_node(node);
        }
      else
        {
          list_del_init(&node->list);
        }
    }
  else
    {
      /* no items either on the wait queue nor the output queue.
       *
       * NOTE: the input queues may contain items even in this case,
       * however we don't touch them here, they'll be migrated to the
       * wait_queue once the input threads finish their processing (or
       * the high watermark is reached). Also, they are unlocked, so
       * no way to touch them safely.
       */
      return FALSE;
    }
  stats_counter_dec(self->super.stored_messages);

  if (push_to_backlog)
    {
      log_msg_ref(*msg);
      list_add_tail(&node->list, &self->qbacklog);
      self->qbacklog_len++;
    }
  if (!ignore_throttle)
    {
      self->super.throttle_buckets--;
    }

  return TRUE;
}

/*
 * Can only run from the output thread.
 */
static void
log_queue_fifo_ack_backlog(LogQueue *s, gint n)
{
  LogQueueFifo *self = (LogQueueFifo *) s;
  LogMessage *msg;
  LogPathOptions path_options = LOG_PATH_OPTIONS_INIT;
  gint i;

  log_queue_assert_output_thread(s);

  for (i = 0; i < n && self->qbacklog_len > 0; i++)
    {
      LogMessageQueueNode *node;

      node = list_entry(self->qbacklog.next, LogMessageQueueNode, list);
      msg = node->msg;
      path_options.ack_needed = node->ack_needed;

      list_del(&node->list);
      log_msg_free_queue_node(node);
      self->qbacklog_len--;

      log_msg_ack(msg, &path_options);
      log_msg_unref(msg);
    }
}


/*
 * log_queue_rewind_backlog:
 *
 * Move items on our backlog back to our qoverflow queue. Please note that this
 * function does not really care about qoverflow size, it has to put the backlog
 * somewhere. The backlog is emptied as that will be filled if we send the
 * items again.
 *
 * NOTE: this is assumed to be called from the output thread.
 */
static void
log_queue_fifo_rewind_backlog(LogQueue *s)
{
  LogQueueFifo *self = (LogQueueFifo *) s;

  log_queue_assert_output_thread(s);

  list_splice_tail_init(&self->qbacklog, &self->qoverflow_output);
  self->qoverflow_output_len += self->qbacklog_len;
  stats_counter_add(self->super.stored_messages, self->qbacklog_len);
  self->qbacklog_len = 0;
}

static void
log_queue_fifo_free_queue(struct list_head *q)
{
  while (!list_empty(q))
    {
      LogMessageQueueNode *node;
      LogPathOptions path_options = LOG_PATH_OPTIONS_INIT;
      LogMessage *msg;

      node = list_entry(q->next, LogMessageQueueNode, list);
      list_del(&node->list);

      path_options.ack_needed = node->ack_needed;
      msg = node->msg;
      log_msg_free_queue_node(node);
      log_msg_ack(msg, &path_options);
      log_msg_unref(msg);
    }
}

static void
log_queue_fifo_free(LogQueue *s)
{
  LogQueueFifo *self = (LogQueueFifo *) s;
  gint i;

  for (i = 0; i < log_queue_max_threads; i++)
    log_queue_fifo_free_queue(&self->qoverflow_input[i].items);

  log_queue_fifo_free_queue(&self->qoverflow_wait);
  log_queue_fifo_free_queue(&self->qoverflow_output);
  log_queue_fifo_free_queue(&self->qbacklog);
  log_queue_free_method(s);
}

LogQueue *
log_queue_fifo_new(gint qoverflow_size, const gchar *persist_name)
{
  LogQueueFifo *self;
  gint i;

  self = g_malloc0(sizeof(LogQueueFifo) + log_queue_max_threads * sizeof(self->qoverflow_input[0]));

  log_queue_init_instance(&self->super, persist_name);
  self->super.get_length = log_queue_fifo_get_length;
  self->super.keep_on_reload = log_queue_fifo_keep_on_reload;
  self->super.push_tail = log_queue_fifo_push_tail;
  self->super.push_head = log_queue_fifo_push_head;
  self->super.pop_head = log_queue_fifo_pop_head;
  self->super.ack_backlog = log_queue_fifo_ack_backlog;
  self->super.rewind_backlog = log_queue_fifo_rewind_backlog;

  self->super.free_fn = log_queue_fifo_free;
  
  for (i = 0; i < log_queue_max_threads; i++)
    {
      INIT_LIST_HEAD(&self->qoverflow_input[i].items);
      main_loop_io_worker_finish_callback_init(&self->qoverflow_input[i].cb);
      self->qoverflow_input[i].cb.user_data = self;
      self->qoverflow_input[i].cb.func = log_queue_fifo_move_input;
    }
  INIT_LIST_HEAD(&self->qoverflow_wait);
  INIT_LIST_HEAD(&self->qoverflow_output);
  INIT_LIST_HEAD(&self->qbacklog);

  self->qoverflow_size = qoverflow_size;
  return &self->super;
}
