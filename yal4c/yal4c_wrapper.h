/* This file is under the GNU Lesser General Public License (https://www.gnu.org/licenses/lgpl-3.0.html)
   A copy of this license is in LICENSE */

#ifndef YAL4C_WRAPPER_INCLUDED
#define YAL4C_WRAPPER_INCLUDED

/* YAL4C 1.2.0+ has a macro for version */
#define YAL4C_VERSION 0x010201

typedef struct yal4c_logfile_struct yal4c_logfile;

void (*yal4c_fatal_func) (void);

char* yal4c_timer (void);
void yal4c_settimer (char* (*) (void));
void yal4c_info (const yal4c_logfile*, const char*);
void yal4c_warn (const yal4c_logfile*, const char*);
void yal4c_error (const yal4c_logfile*, const char*);
void yal4c_fatal (const yal4c_logfile*, const char*);
void yal4c_debug (const yal4c_logfile*, const char*);
void yal4c_enable_debug (void);
int yal4c_info_counter (void);
int yal4c_warn_counter (void);
int yal4c_error_counter (void);
int yal4c_debug_counter (void);

yal4c_logfile* yal4c_open_log (int, const char*);
int yal4c_close (const yal4c_logfile*);

#endif
