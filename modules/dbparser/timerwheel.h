#ifndef TIMERWHEEL_H_INCLUDED
#define TIMERWHEEL_H_INCLUDED

#include "syslog-ng.h"

typedef struct _TWEntry TWEntry;
typedef void (*TWCallbackFunc)(guint64 now, gpointer user_data);
typedef struct _TimerWheel TimerWheel;

TWEntry *timer_wheel_add_timer(TimerWheel *self, gint timeout, TWCallbackFunc cb, gpointer user_data, GDestroyNotify user_data_free);
void timer_wheel_del_timer(TimerWheel *self, TWEntry *entry);
void timer_wheel_mod_timer(TimerWheel *self, TWEntry *entry, gint new_timeout);
guint64 timer_wheel_get_timer_expiration(TimerWheel *self, TWEntry *entry);

void timer_wheel_set_time(TimerWheel *self, guint64 new_now);
guint64 timer_wheel_get_time(TimerWheel *self);
void timer_wheel_expire_all(TimerWheel *self);
TimerWheel *timer_wheel_new(void);
void timer_wheel_free(TimerWheel *self);


#endif
