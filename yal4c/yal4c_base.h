/* This file is under the GNU Lesser General Public License (https://www.gnu.org/licenses/lgpl-3.0.html)
   A copy of this license is in LICENSE */

#ifndef YAL4C_BASE_INCLUDED
#define YAL4C_BASE_INCLUDED

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#define mutex CRITICAL_SECTION
#define mutex_init InitializeCriticalSection
#define mutex_lock EnterCriticalSection
#define mutex_unlock LeaveCriticalSection
#define mutex_destroy DeleteCriticalSection
#elif defined (__linux)
#include <pthread.h>
#define mutex pthread_mutex_t
#define mutex_init(a) pthread_mutex_init(a, NULL)
#define mutex_lock pthread_mutex_lock
#define mutex_unlock pthread_mutex_unlock
#define mutex_destroy pthread_mutex_destroy
#else
#error YAL4C 1.2.0+ does not support platforms except Windows and Linux. Try to edit yal4c_base.h to make it work?
#endif

typedef struct yal4c_logfile_struct
{
    const int standard;
    const int backupfile;
    mutex lock;
} yal4c_logfile;

extern yal4c_logfile* yal4c_open_log (int, const char*);
extern int yal4c_write (yal4c_logfile*, const char*);
extern int yal4c_close (yal4c_logfile*);

#endif
