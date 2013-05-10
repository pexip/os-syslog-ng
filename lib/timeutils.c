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

#include "timeutils.h"
#include "messages.h"
#include "syslog-ng.h"
#include "tls-support.h"

#include <ctype.h>
#include <string.h>
#include <iv.h>

const char *month_names_abbrev[] =
{
  "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

const char *month_names[] =
{
  "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
};

const char *weekday_names_abbrev[] =
{
  "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

const char *weekday_names[] =
{
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};


#define TZCACHE_SIZE 4
#define TZCACHE_SIZE_MASK (TZCACHE_SIZE - 1)
#define TZ_MAGIC "TZif"

const gint64 LOWEST_TIME32    = (gint64)((gint32)0x80000000);
static const gchar *time_zone_path_list[] = 
{ 
#ifdef PATH_TIMEZONEDIR
  PATH_TIMEZONEDIR,               /* search the user specified dir */
#endif
  PATH_PREFIX "/share/zoneinfo/", /* then local installation first */
  "/usr/share/zoneinfo/",         /* linux */
  "/usr/share/lib/zoneinfo/",     /* solaris, AIX */
  NULL,
};

static const gchar *time_zone_basedir = NULL;

typedef struct _TimeCache
{
  time_t when;
  struct tm tm;
} TimeCache;

static const gchar *
get_time_zone_basedir(void)
{
  int i = 0;

  if (!time_zone_basedir)
    {
      for (i = 0; time_zone_path_list[i] != NULL && !g_file_test(time_zone_path_list[i], G_FILE_TEST_IS_DIR); i++)
        ;
      time_zone_basedir = time_zone_path_list[i];
    }
  return time_zone_basedir;
}

TLS_BLOCK_START
{
  GTimeVal current_time_value;
  struct iv_task invalidate_time_task;
  TimeCache local_time_cache[64];
  TimeCache gm_time_cache[64];
  struct tm mktime_prev_tm;
  time_t mktime_prev_time;
}
TLS_BLOCK_END;

#define current_time_value   __tls_deref(current_time_value)
#define invalidate_time_task __tls_deref(invalidate_time_task)
#define local_time_cache     __tls_deref(local_time_cache)
#define gm_time_cache        __tls_deref(gm_time_cache)
#define mktime_prev_tm       __tls_deref(mktime_prev_tm)
#define mktime_prev_time     __tls_deref(mktime_prev_time)

#if !defined(HAVE_LOCALTIME_R) || !defined(HAVE_GMTIME_R)
static GStaticMutex localtime_lock = G_STATIC_MUTEX_INIT;
#endif

void
invalidate_cached_time(void)
{
  current_time_value.tv_sec = 0;
}

/*
 * this shuld replace the g_get_current_time and the g_source_get_current_time calls in the main thread
 * (log_msg_init, afinter_postpone_mark)
 */
void
cached_g_current_time(GTimeVal *result)
{
  if (current_time_value.tv_sec == 0)
    {
      g_get_current_time(&current_time_value);
    }
  *result = current_time_value;

  if (iv_inited())
    {
      if (invalidate_time_task.handler == NULL)
        {
          IV_TASK_INIT(&invalidate_time_task);
          invalidate_time_task.handler = (void (*)(void *)) invalidate_cached_time;
        }
      if (!iv_task_registered(&invalidate_time_task))
        iv_task_register(&invalidate_time_task);
    }
  else
    {
      invalidate_cached_time();
    }
}

time_t
cached_g_current_time_sec()
{
  GTimeVal now;

  cached_g_current_time(&now);
  return now.tv_sec;
}

time_t
cached_mktime(struct tm *tm)
{
  time_t result;

  if (G_LIKELY(tm->tm_sec == mktime_prev_tm.tm_sec &&
               tm->tm_min == mktime_prev_tm.tm_min &&
               tm->tm_hour == mktime_prev_tm.tm_hour &&
               tm->tm_mday == mktime_prev_tm.tm_mday &&
               tm->tm_mon == mktime_prev_tm.tm_mon &&
               tm->tm_year == mktime_prev_tm.tm_year))
    {
      result = mktime_prev_time;
      return result;
    }
  result = mktime(tm);
  mktime_prev_tm = *tm;
  mktime_prev_time = result;
  return result;
}

void
cached_localtime(time_t *when, struct tm *tm)
{
  guchar i = 0;

  i = *when & 0x3F;
  if (G_LIKELY(*when == local_time_cache[i].when))
    {
      *tm = local_time_cache[i].tm;
      return;
    }
  else
    {
#ifdef HAVE_LOCALTIME_R
      localtime_r(when, tm);
#else
      struct tm *ltm;

      g_static_mutex_lock(&localtime_lock);
      ltm = localtime(when);
      *tm = *ltm;
      g_static_mutex_unlock(&localtime_lock);
#endif
      local_time_cache[i].tm = *tm;
      local_time_cache[i].when = *when;
    }
}

void
cached_gmtime(time_t *when, struct tm *tm)
{
  guchar i = 0;

  i = *when & 0x3F;
  if (G_LIKELY(*when == gm_time_cache[i].when))
    {
      *tm = gm_time_cache[i].tm;
      return;
    }
  else
    {
#ifdef HAVE_GMTIME_R
      gmtime_r(when, tm);
#else
      struct tm *ltm;

      g_static_mutex_lock(&localtime_lock);
      ltm = gmtime(when);
      *tm = *ltm;
      g_static_mutex_unlock(&localtime_lock);
#endif
      gm_time_cache[i].tm = *tm;
      gm_time_cache[i].when = *when;
    }
}

/**
 * get_local_timezone_ofs:
 * @when: time in UTC
 * 
 * Return the zone offset (measured in seconds) of @when expressed in local
 * time. The function also takes care about daylight saving.
 **/
long
get_local_timezone_ofs(time_t when)
{
#ifdef HAVE_STRUCT_TM_TM_GMTOFF
  struct tm ltm;

  cached_localtime(&when, &ltm);
  return ltm.tm_gmtoff;

#else

  struct tm gtm;
  struct tm ltm;
  long tzoff;
  
  cached_localtime(&when, &ltm);
  cached_gmtime(&when, &gtm);

  tzoff = (ltm.tm_hour - gtm.tm_hour) * 3600;
  tzoff += (ltm.tm_min - gtm.tm_min) * 60;
  tzoff += ltm.tm_sec - gtm.tm_sec;
  
  if (tzoff > 0 && (ltm.tm_year < gtm.tm_year || ltm.tm_mon < gtm.tm_mon || ltm.tm_mday < gtm.tm_mday))
    tzoff -= 86400;
  else if (tzoff < 0 && (ltm.tm_year > gtm.tm_year || ltm.tm_mon > gtm.tm_mon || ltm.tm_mday > gtm.tm_mday))
    tzoff += 86400;
  
  return tzoff;
#endif /* HAVE_STRUCT_TM_TM_GMTOFF */
}


void
clean_time_cache()
{
  memset(&gm_time_cache, 0, sizeof(gm_time_cache));
  memset(&local_time_cache, 0, sizeof(local_time_cache));
}

int
format_zone_info(gchar *buf, size_t buflen, glong gmtoff)
{
  return g_snprintf(buf, buflen, "%c%02ld:%02ld",
                          gmtoff < 0 ? '-' : '+',
                          (gmtoff < 0 ? -gmtoff : gmtoff) / 3600,
                          ((gmtoff < 0 ? -gmtoff : gmtoff) % 3600) / 60);
}

/**
 * check_nanosleep:
 *
 * Check if nanosleep() is accurate enough for sub-millisecond sleeping. If
 * it is not good enough, we're skipping the minor sleeps in LogReader to
 * balance the cost of returning to the main loop (e.g.  we're always going
 * to return to the main loop, instead of trying to wait for the writer).
 **/
gboolean
check_nanosleep(void)
{
#ifdef HAVE_CLOCK_GETTIME
  struct timespec start, stop, sleep;
  glong diff;
  gint attempts;

  for (attempts = 0; attempts < 3; attempts++)
    {
      clock_gettime(CLOCK_MONOTONIC, &start);
      sleep.tv_sec = 0;
      /* 0.1 msec */
      sleep.tv_nsec = 1e5;

      while (nanosleep(&sleep, &sleep) < 0)
        ;

      clock_gettime(CLOCK_MONOTONIC, &stop);
      diff = timespec_diff_nsec(&stop, &start);
      if (diff < 5e5)
        return TRUE;
    }
#endif
  return FALSE;
}

/**
 * g_time_val_diff:
 * @t1: time value t1
 * @t2: time value t2
 *
 * Calculates the time difference between t1 and t2 in microseconds.
 * The result is positive if t1 is later than t2.
 *
 * Returns:
 * Time difference in microseconds
 */
glong
g_time_val_diff(GTimeVal *t1, GTimeVal *t2)
{
  g_assert(t1);
  g_assert(t2);
  return (t1->tv_sec - t2->tv_sec) * G_USEC_PER_SEC + (t1->tv_usec - t2->tv_usec);
}

void
timespec_add_msec(struct timespec *ts, glong msec)
{
  ts->tv_sec += msec / 1000;
  msec = msec % 1000;
  ts->tv_nsec += msec * 1e6;
  if (ts->tv_nsec > 1e9)
    {
      ts->tv_nsec -= 1e9;
      ts->tv_sec++;
    }
}

glong
timspec_diff_msec(struct timespec *t1, struct timespec *t2)
{
  return (t1->tv_sec - t2->tv_sec) * 1e3 + (t1->tv_nsec - t2->tv_nsec) / 1e6;
}

glong
timespec_diff_nsec(struct timespec *t1, struct timespec *t2)
{
  return (t1->tv_sec - t2->tv_sec) * 1e9 + (t1->tv_nsec - t2->tv_nsec);
}

/** Time zone file parser code **/

/*
 ** TZ file header **
 *
 *  struct tzhead 
 *    {
 *       char    tzh_magic[4];            TZ_MAGIC "TZif"
 *       char    tzh_version[1];          '\0' or '2' as of 2005 
 *       char    tzh_reserved[15];        reserved--must be zero 
 *       char    tzh_ttisgmtcnt[4];       coded number of trans. time flags 
 *       char    tzh_ttisstdcnt[4];       coded number of trans. time flags 
 *       char    tzh_leapcnt[4];          coded number of leap seconds 
 *       char    tzh_timecnt[4];          coded number of transition times 
 *       char    tzh_typecnt[4];          coded number of local time types 
 *       char    tzh_charcnt[4];          coded number of abbr. chars 
 *    };
 *
 ** TZ file body part **
 *
 *      tzh_timecnt (char [4])s         coded transition times a la time(2)
 *      tzh_timecnt (unsigned char)s    types of local time starting at above
 *      tzh_typecnt repetitions of
 *              one (char [4])          coded UTC offset in seconds
 *              one (unsigned char)     used to set tm_isdst
 *              one (unsigned char)     that's an abbreviation list index
 *      tzh_charcnt (char)s             '\0'-terminated zone abbreviations
 *      tzh_leapcnt repetitions of
 *              one (char [4])          coded leap second transition times
 *              one (char [4])          total correction after above
 *      tzh_ttisstdcnt (char)s          indexed by type; if TRUE, transition time is standard time, if FALSE, transition time is wall clock time if absent, 
 *                                      transition times are assumed to be wall clock time 
 *      tzh_ttisgmtcnt (char)s          indexed by type; if TRUE, transition time is UTC, if FALSE, transition time is local time if absent, 
 *                                      transition times are assumed to be local time
 */

/*
 * A transition from one ZoneType to another
 * Minimal size = 5 bytes (4+1)
 */
typedef struct _Transition
{
  gint64 time;        /* seconds, 1970 epoch */
  gint32 gmtoffset;   /* raw seconds offset from GMT */
}Transition;

/* A collection of transitions from one zone_type to another, together
 * with a list of the zone_types.  A zone_info object may have a long
 * list of transitions between a smaller list of zone_types.
 *
 * This object represents the contents of a single zic-created
 * zoneinfo file.
 */
struct _ZoneInfo
{
  Transition *transitions;
  gint64 timecnt; 
  gint32 last_transitions_index;
};

struct _TimeZoneInfo
{
  ZoneInfo *zone;
  ZoneInfo *zone64;
  glong zone_offset;
};

/* Read zic-coded 32-bit integer from file*/
static gint64
readcoded32(unsigned char **input, gint64 minv, gint64 maxv)
{
  unsigned char buf[4]; /* must be UNSIGNED */
  gint64 val = 0;
  gint32 i = 0;
  gint32 shift = 0;

  memcpy (buf, *input, sizeof(buf));
  *input += 4;

  for (i = 0, shift = 24; i < 4; ++i, shift -= 8)
    val |= buf[i] << shift;

  if (val < minv || val > maxv)
    {
      msg_error("Error while processing the time zone file", 
                evt_tag_str("message", "oded value out-of-range"), 
                evt_tag_int("value", val),
                evt_tag_printf("expected", "[%"G_GINT64_FORMAT", %"G_GINT64_FORMAT"]", minv, maxv), 
                NULL);
      g_assert_not_reached();
    }
  return val;
}

/* Read zic-coded 64-bit integer from file */
static gint64 
readcoded64(unsigned char **input, gint64 minv, gint64 maxv)
{
  unsigned char buf[8]; /* must be UNSIGNED */
  gint64 val = 0;
  gint32 i = 0;
  gint32 shift = 0;

  memcpy (buf, *input, sizeof(buf));
  *input += 8;

  for (i = 0, shift = 56; i < 8; ++i, shift -= 8)
    val |= (gint64)buf[i] << shift;

  if (val < minv || val > maxv)
    {
      msg_error("Error while processing the time zone file",
                evt_tag_str("message", "Coded value out-of-range"), 
                evt_tag_int("value", val), 
                evt_tag_printf("expected", "[%"G_GINT64_FORMAT", %"G_GINT64_FORMAT"]", minv, maxv), 
                NULL);
      g_assert_not_reached();
    }
  return val;
}

/* Read a booleanean value */
static gboolean 
readbool(unsigned char **input)
{
  gchar c;

  c = **input;
  *input += 1;

  if (c!=0 && c!=1)
    {
      msg_error("Error while processing the time zone file",
                evt_tag_str("message", "Boolean value out-of-range"), 
                evt_tag_int("value", c), 
                NULL);
      g_assert_not_reached();
    }
  return (c != 0);
}

/* Read a character value */
static gchar 
readchar(unsigned char **input)
{
  unsigned char c;

  c = **input;
  *input += 1;

  return c;
}

static ZoneInfo*
zone_info_new(gint64 timecnt)
{
  ZoneInfo *self = g_new0(ZoneInfo,  1);

  self->transitions = g_new0(Transition, timecnt);
  self->timecnt = timecnt;
  self->last_transitions_index = -1;
  return self;
}

static void
zone_info_free(ZoneInfo *self)
{
  if (!self)
    return;

  g_free(self->transitions);
  g_free(self);
}

/**
 * Parse the zoneinfo file structure (see tzfile.h) into a ZoneInfo
 */
static ZoneInfo*
zone_info_parser(unsigned char **input, gboolean is64bitData, gint *version)
{
  gint32 i = 0;
  unsigned char *buf = NULL;
  ZoneInfo *info = NULL;
  gint64 *transition_times = NULL;
  guint8 *transition_types = NULL;
  gint32 *gmt_offsets = NULL;
  gint64 isgmtcnt, isdstcnt, leapcnt, timecnt, typecnt, charcnt;
  gboolean insertInitial = FALSE;

  buf = *input;
  *input += 4;

  if (strncmp((gchar*)buf, TZ_MAGIC, 4) != 0)
    {
      msg_error("Error while processing the time zone file", 
                evt_tag_str("message", TZ_MAGIC" signature is missing"), 
                NULL);
      goto error;
    }
  
  /* read the version byte */
  buf = *input;
  *input += 1;

  /*
   * if '\0', we have just one copy of data,
   * if '2', there is additional 64 bit version at the end.
   */
  if (buf[0] != 0 && buf[0] != '2')
    {
      msg_error("Error in the time zone file", 
                evt_tag_str("message", "Bad Olson version info"), 
                NULL);
      goto error;
    }
  else 
    {
      if (buf[0] != 0)
        *version = buf[0] - '0';
      else
        *version = 0;
    }

  /* Read reserved bytes */
  *input += 15;

  /* Read array sizes */
  isgmtcnt = readcoded32(input, 0, G_MAXINT64);
  isdstcnt = readcoded32(input, 0, G_MAXINT64);
  leapcnt  = readcoded32(input, 0, G_MAXINT64);
  timecnt  = readcoded32(input, 0, G_MAXINT64);
  typecnt  = readcoded32(input, 0, G_MAXINT64);
  charcnt  = readcoded32(input, 0, G_MAXINT64);

  /* 
   * Confirm sizes that we assume to be equal.  These assumptions
   * are drawn from a reading of the zic source (2003a), so they
   * should hold unless the zic source changes. 
   */

  if (isgmtcnt != typecnt || 
      isdstcnt != typecnt) 
    {
      msg_warning("Error in the time zone file", 
                   evt_tag_str("message", "Count mismatch between tzh_ttisgmtcnt, tzh_ttisdstcnt, tth_typecnt"), 
                   NULL);
    }

  /* 
   * Used temporarily to store transition times and types.  We need
   * to do this because the times and types are stored in two
   * separate arrays.
   */
  transition_times = g_new0(gint64, timecnt);
  transition_types = g_new0(guint8, timecnt);
  gmt_offsets      = g_new0(gint32, typecnt);

  /* Read transition times */
  for (i = 0; i < timecnt; ++i)
    {
      if (is64bitData) 
        {
          transition_times[i] = readcoded64(input, G_MININT64, G_MAXINT64);
        }
      else
        {
          transition_times[i] = readcoded32(input, G_MININT64, G_MAXINT64);
        }
    }
  
  /* Read transition types */
  for (i = 0; i < timecnt; ++i)
    {
      guint8 t = (guint8)readchar(input);
      if (t >= typecnt)
        {
          msg_warning("Error in the time zone file", 
                      evt_tag_str("message", "Illegal type number"), 
                      evt_tag_printf("val", "%ld", (long) t), 
                      evt_tag_printf("expected", "[0, %" G_GINT64_FORMAT "]", typecnt-1), 
                      NULL);
          goto error;
        }
      transition_types[i] = t;
    }

 /* Read types (except for the isstd and isgmt flags, which come later (why??)) */
  for (i = 0; i<typecnt; ++i)
    {
      gmt_offsets[i] = readcoded32(input, G_MININT64, G_MAXINT64);
      if (gmt_offsets[i] > 24 * 60 * 60 || gmt_offsets[i] < -1 * 24 * 60 * 60)
        {
          msg_warning("Error in the time zone file", 
                      evt_tag_str("message", "Illegal gmtoffset number"), 
                      evt_tag_int("val", gmt_offsets[i]), 
                      evt_tag_printf("expected", "[%d, %d]", -1 * 24 * 60 * 60, 24 * 60 * 60), 
                      NULL);
          goto error;
        }
      /* ignore isdst flag */ 
      readbool(input);
      /* ignore abbr index */
      readchar(input);
    }

  /* allocate a new ZoneInfo structure */
  if (typecnt > 0 && timecnt == 0)
    {
      /* only one type info is in the time zone file so add it with 1901 */
      info = zone_info_new(1);
      info->transitions[0].time = LOWEST_TIME32;
      info->transitions[0].gmtoffset = gmt_offsets[0];
    }
  else
    {
      info = zone_info_new(timecnt);
    }
 
  /* Build transitions vector out of corresponding times and types. */
  insertInitial = FALSE;
  if (is64bitData)
    {
      if (timecnt > 0)
        {
          gint32 minidx = -1;
          gint32 last_transition_index = 0;
          for (i = 0; i < timecnt; ++i)
            {
              if (transition_times[i] < LOWEST_TIME32)
                {
                  if (minidx == -1 || transition_times[i] > transition_times[minidx])
                    {
                      /* Preserve the latest transition before the 32bit minimum time */
                      minidx = i;
                    }
                }
              else
                {
                  info->transitions[last_transition_index].time = transition_times[i];
                  info->transitions[last_transition_index].gmtoffset = gmt_offsets[transition_types[i]];
                  last_transition_index++;
                }
            }

          if (minidx != -1)
            {
              /* 
               * If there are any transitions before the 32bit minimum time,
               * put the type information with the 32bit minimum time
               */
              memmove(&info->transitions[1], &info->transitions[0], sizeof(Transition) * (timecnt-1));
              info->transitions[0].time = LOWEST_TIME32;
              info->transitions[0].gmtoffset = gmt_offsets[transition_types[minidx]];
              info->timecnt -= minidx;
            }
          else
            {
              /* Otherwise, we need insert the initial type later */
              insertInitial = TRUE;
            }
        }
    }
  else
    {
      for (i = 0; i < timecnt; ++i)
        {
          info->transitions[i].time = transition_times[i];        
          info->transitions[i].gmtoffset = gmt_offsets[transition_types[i]];
        }
    }

  if (insertInitial)
    {
      g_assert(timecnt > 0);
      g_assert(typecnt > 0);

      /* reallocate the transitions vector to be able to store a new entry */
      info->timecnt ++;
      timecnt ++;
      info->transitions = g_renew(Transition, info->transitions, timecnt);

      /* Add the initial type associated with the lowest int32 time */
      memmove(&info->transitions[1], &info->transitions[0], sizeof(Transition) * (timecnt-1));
      info->transitions[0].time = LOWEST_TIME32;
      info->transitions[0].gmtoffset = gmt_offsets[0];
    }

  /* ignore the abbreviation string */
  if (charcnt)
    *input += charcnt;

  /* ignore leap second info, if any */
  for (i=0; i<leapcnt; ++i)
    {
      if(is64bitData)
        readcoded64(input, G_MININT64, G_MAXINT64);/* leap second transition time */
      else
        readcoded32(input, G_MININT64, G_MAXINT64);/* leap second transition time */
      readcoded32(input, G_MININT64, G_MAXINT64);/* total correction after above */
    }

  /* http://osdir.com/ml/time.tz/2006-02/msg00041.html */
  /* We dont nead this flags to compute the wall time of the timezone*/

  /* Ignore isstd flags */
  for (i=0;i<typecnt;i++)
    readbool(input);

  /* Ignore isgmt flags */
  for (i=0;i<typecnt;i++)
    readbool(input);

error:
  g_free(transition_times);
  g_free(transition_types);
  g_free(gmt_offsets);
  return info;
}

static gint64
zone_info_get_offset(ZoneInfo *self, gint64 timestamp)
{
  gint32 i = 0;

  if (self->transitions == NULL)
    return 0;

  if (self->last_transitions_index != -1 && 
     self->last_transitions_index < (self->timecnt - 1) && 
     self->transitions[self->last_transitions_index].time < timestamp &&  
     self->transitions[self->last_transitions_index + 1].time > timestamp)
    {
      return  self->transitions[ self->last_transitions_index ].gmtoffset;
    }
  else
    {
      for (i = 0; i < (self->timecnt - 1); i++)
        if (self->transitions[i].time < timestamp && 
            self->transitions[i+1].time > timestamp)
          break;
 
      self->last_transitions_index  = i;
    }
 
  return self->transitions[self->last_transitions_index].gmtoffset;
}

static gboolean
zone_info_read(const gchar *zonename, ZoneInfo **zone, ZoneInfo **zone64)
{
  unsigned char *buff = NULL;
  gchar *filename = NULL; 
  int byte_read = 0;
  int version;
  GError *error = NULL;
  GMappedFile *file_map = NULL;

  *zone = NULL;
  *zone64 = NULL;

  filename = g_build_path(G_DIR_SEPARATOR_S, get_time_zone_basedir(), zonename, NULL);

  file_map = g_mapped_file_new(filename, FALSE, &error);
  if (!file_map)
    {
      msg_error("Failed to open the time zone file", evt_tag_str("filename", filename), evt_tag_str("message", error->message), NULL);
      g_error_free(error);
      g_free(filename);
      return FALSE;
    }

  byte_read = g_mapped_file_get_length(file_map);
  buff = (unsigned char*)g_mapped_file_get_contents(file_map);

  if (byte_read == -1)
    {
      msg_error("Failed to read the time zone file", evt_tag_str("filename", filename), NULL);
      g_mapped_file_free(file_map);
      g_free(filename);
      return FALSE;
    }

  msg_debug("Processing the time zone file (32bit part)", evt_tag_str("filename", filename), NULL);
  *zone = zone_info_parser(&buff, FALSE, &version);
  if (version == 2)
    {
      msg_debug("Processing the time zone file (64bit part)", evt_tag_str("filename", filename), NULL);
      *zone64 = zone_info_parser(&buff, TRUE, &version);
    }

  g_mapped_file_free(file_map);
    g_free(filename);
  return TRUE;
}

gint32
time_zone_info_get_offset(const TimeZoneInfo *self, time_t stamp)
{
  if (self == NULL)
    return -1;

  if (self->zone_offset != -1)
    return self->zone_offset;

  if (self->zone64)
    return zone_info_get_offset(self->zone64, stamp);

  if (self->zone)
    return zone_info_get_offset(self->zone, stamp);

  return -1;
}

TimeZoneInfo*
time_zone_info_new(const gchar *tz)
{
  TimeZoneInfo *self = g_new0(TimeZoneInfo,1);
  self->zone_offset = -1;
 
  /* if no time zone was specified return with an empty TimeZoneInfo pointer */  
  if (!tz)
    return self;

  if ((*tz == '+' || *tz == '-') && strlen(tz) == 6 && 
      isdigit((int) *(tz+1)) && isdigit((int) *(tz+2)) && 
      (*(tz+3) == ':') && isdigit((int) *(tz+4)) && 
      isdigit((int) *(tz+5)))
    {
      /* timezone offset */
      gint sign = *tz == '-' ? -1 : 1;
      gint hours, mins;
      tz++;
      
      hours = (*tz - '0') * 10 + *(tz+1) - '0';
      mins = (*(tz+3) - '0') * 10 + *(tz+4) - '0';
      if ((hours < 24 && mins <= 60) || (hours == 24 && mins == 0))
        {
          self->zone_offset = sign * (hours * 3600 + mins * 60);
          return self;
        }
    }
  else if (zone_info_read(tz, &self->zone, &self->zone64))
    {
      return self;
    }

  time_zone_info_free(self);

  /* failed to read time zone data */
  msg_error("Bogus timezone spec, must be in the format [+-]HH:MM, offset must be less than 24:00",
            evt_tag_str("value", tz),
            NULL);
  return NULL;
}

void 
time_zone_info_free(TimeZoneInfo *self)
{
  g_assert(self);

  zone_info_free(self->zone);
  zone_info_free(self->zone64);
  g_free(self);
}

