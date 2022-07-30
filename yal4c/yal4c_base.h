/* This file is under the GNU Lesser General Public License (https://www.gnu.org/licenses/lgpl-3.0.html)
   A copy of this license is in LICENSE */

#ifndef YAL4C_BASE_INCLUDED
#define YAL4C_BASE_INCLUDED

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct yal4c_logfile_struct
{
    volatile int standard;
    volatile int backupfile;
    volatile int lock;
} yal4c_logfile;

extern yal4c_logfile* yal4c_open_log (int, const char*);
extern int yal4c_write (yal4c_logfile*, const char*);
extern int yal4c_close (yal4c_logfile*);

#endif
