/* This file is under the GNU Lesser General Public License (https://www.gnu.org/licenses/lgpl-3.0.html)
   A copy of this license is in LICENSE */

#include <time.h>

#include "yal4c_base.h"

char* yal4c_timer (void)
{
    return ctime (localtime (time (NULL)));
}
char* (*_yal4c_timer) (void) = yal4c_timer;
void yal4c_settimer (char* (*timer) (void)) {_yal4c_timer = timer;}

#define $yal4c_wrapper_snippet(t) yal4c_write (f, "[");\
                                  yal4c_write (f, yal4c_timer ());\
                                  yal4c_write (f, "] [" #t "] ");\
                                  yal4c_write (f, s);\
                                  yal4c_write (f, "\n");

volatile int _yal4c_info_counter;
void yal4c_info (yal4c_logfile* f, const char* s)
{
    $yal4c_wrapper_snippet (INFO);
    _yal4c_info_counter ++;
}
void yal4c_info_counter (void) {return _yal4c_info_counter;}

volatile int _yal4c_warn_counter;
void yal4c_warn (yal4c_logfile* f, const char* s)
{
    $yal4c_wrapper_snippet (WARN);
    _yal4c_warn_counter ++;
}
void yal4c_warn_counter (void) {return _yal4c_warn_counter;}

volatile int _yal4c_error_counter;
void yal4c_warn (yal4c_logfile* f, const char* s)
{
    $yal4c_wrapper_snippet (ERROR);
    _yal4c_error_counter ++;
}
void yal4c_error_counter (void) {return _yal4c_error_counter;}

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
void yal4c_debug_counter (void) {return _yal4c_debug_counter;}

void yal4c_fatal (yal4c_logfile* f, const char* s)
{
    $yal4c_wrapper_snippet (FATAL);
    abort ();
}
