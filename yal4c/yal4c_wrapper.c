/* This file is under the GNU Lesser General Public License (https://www.gnu.org/licenses/lgpl-3.0.html)
   A copy of this license is in LICENSE */

#include <time.h>

#include "yal4c_base.h"

char* yal4c_timer (void)
{
    time_t t = time (NULL);
    char* res = ctime (&t);
    res [24] = 0;
    return res;
}
char* (*_yal4c_timer) (void) = yal4c_timer;
void yal4c_settimer (char* (*timer) (void)) {_yal4c_timer = timer;}

#define $yal4c_wrapper_snippet(t) mutex_lock (&(f -> lock));       \
                                  yal4c_write (f, "[");            \
                                  yal4c_write (f, _yal4c_timer ());\
                                  yal4c_write (f, "] [" #t "] ");  \
                                  yal4c_write (f, s);              \
                                  yal4c_write (f, "\n");           \
                                  mutex_unlock (&(f -> lock));     \

volatile int _yal4c_info_counter;
void yal4c_info (yal4c_logfile* f, const char* s)
{
    $yal4c_wrapper_snippet (INFO);
    _yal4c_info_counter ++;
}
int yal4c_info_counter (void) {return _yal4c_info_counter;}

volatile int _yal4c_warn_counter;
void yal4c_warn (yal4c_logfile* f, const char* s)
{
    $yal4c_wrapper_snippet (WARN);
    _yal4c_warn_counter ++;
}
int yal4c_warn_counter (void) {return _yal4c_warn_counter;}

volatile int _yal4c_error_counter;
void yal4c_error (yal4c_logfile* f, const char* s)
{
    $yal4c_wrapper_snippet (ERROR);
    _yal4c_error_counter ++;
}
int yal4c_error_counter (void) {return _yal4c_error_counter;}

volatile int _yal4c_debug_counter, _yal4c_debug_enabled;
void yal4c_enable_debug (void)
{
    _yal4c_debug_enabled = 1;
}
void yal4c_debug (yal4c_logfile* f, const char* s)
{
    if (! _yal4c_debug_enabled) return;
    $yal4c_wrapper_snippet (DEBUG);
    _yal4c_debug_counter ++;
}
int yal4c_debug_counter (void) {return _yal4c_debug_counter;}

void (*yal4c_fatal_func) (void) = abort;
void yal4c_fatal (yal4c_logfile* f, const char* s)
{
    $yal4c_wrapper_snippet (FATAL);
    yal4c_fatal_func ();
}
