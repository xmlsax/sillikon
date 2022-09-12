#include "yal4c_wrapper.h"
#include <stdio.h>
#include <stdlib.h>

char* t (void) {return ";p";}

int main (void)
{
    const yal4c_logfile* log = yal4c_open_log (1 /* stdout */, "test.log");
    printf ("%p\n", log);
    
    yal4c_settimer (t);
    
    yal4c_info (log, "This is INFO!");
    
    yal4c_debug (log, "Should not appear...");
    
    yal4c_error (log, "Nop no error");
    
    yal4c_enable_debug ();
    
    yal4c_debug (log, "Uhhhhhhhhhhh");
    
    printf ("%d of INFO, %d of ERROR, %d of DEBUG\n", yal4c_info_counter (), yal4c_error_counter (), yal4c_debug_counter ());
    
    int t; scanf ("%d", &t); /* Waiting for user to continue */

    yal4c_fatal_func = NULL; /* Is it Segmentation Fault? Yep */

    yal4c_fatal (log, "Errrrrr...");
}
