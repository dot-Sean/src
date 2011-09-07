#include "rtrim.h"
/* fprintf() */
#include <stdio.h>
/* strdup() */
#include <string.h>
/* free() */
#include <stdlib.h>

#include <mcheck.h>

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  char * psz = NULL;
    mtrace();
    do {
        psz = strdup("Hello World \n \t   ");
        rtrim(psz);
        fprintf(stderr, "d: \"%s\"\n", psz);
        rc = 0;
    } while (0);
    if (psz) { free(psz); }
    muntrace();
    return (rc);
}
