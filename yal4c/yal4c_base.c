/* This file is under the GNU Lesser General Public License (https://www.gnu.org/licenses/lgpl-3.0.html)
   A copy of this license is in LICENSE */

#include "yal4c_base.h"

yal4c_logfile* yal4c_open_log (int standard, const char* fn)
{
    if (standard == -1) goto yal4c$open$ret;
    yal4c_logfile* log = malloc (sizeof (yal4c_logfile));
    if (log == NULL) goto yal4c$open$ret;
    log -> lock = 0;
    * ((int*) (&(log -> standard))) = standard;
    * ((int*) (&(log -> backupfile))) = open (fn, O_WRONLY | O_CREAT, 511);
    if (log -> backupfile == -1)
    {
        free (log);
        goto yal4c$open$ret;
    }
    return log;
    yal4c$open$ret:
    return NULL;
}

void yal4c_lock (yal4c_logfile* f)
{
    while (f -> lock);
    f -> lock = 1;
}

void yal4c_unlock (yal4c_logfile* f)
{
    f -> lock = 0;
}

int yal4c_write (yal4c_logfile* f, const char* s)
{
    unsigned int l = strlen (s);
    int a = write (f -> standard, s, l);
    int b = write (f -> backupfile, s, l);
    return a > b ? b : a;
}

int yal4c_close (yal4c_logfile* f)
{
    close (f -> standard);
    close (f -> backupfile);
    /* Free it */
    #ifndef YAL4C_CLOSE_NO_FREE
    free (f);
    #endif
    return 0;
}
