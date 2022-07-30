/* This file is under the GNU Lesser General Public License (https://www.gnu.org/licenses/lgpl-3.0.html)
   A copy of this license is in LICENSE */

#include "yal4c_base.h"

yal4c_logfile* yal4c_open (int standard, const char* fn)
{
    if (standard == -1) goto yal4c$open$ret;
    yal4c_logfile* log = malloc (sizeof (yal4c_logfile));
    if (log == NULL) goto yal4c$open$ret;
    log -> lock = 0;
    log -> standard = standard;
    log -> backupfile = open (fn, O_WRONLY | O_TRUNC | O_BINARY);
    if (log -> backupfile == -1)
    {
        free (log);
        goto yal4c$open$ret;
    }
    return log;
    yal4c$open$ret:
    return NULL;
}

int yal4c_write (yal4c_logfile* f, const char* s)
{
    unsigned int l = strlen (s);
    while (f -> lock);
    f -> lock = 1;
    int a = write (f -> standard, s, l);
    int b = write (f -> backupfile, s, l);
    f -> lock = 0;
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
