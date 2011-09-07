#include "trim.h"
/* fprintf() */
#include <stdio.h>
/* strdup() */
#include <string.h>
/* free() */
#include <stdlib.h>

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  char * psz = NULL;
    do {
        psz = strdup("    \t\tHello World \n \t   ");
        trim(psz);
        fprintf(stderr, "d: \"%s\"\n", psz);
        rc = 0;
    } while (0);
    if (psz) { free(psz); }
    return (rc);
}
