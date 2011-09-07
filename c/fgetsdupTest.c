/* fgetsdup() */
#include "fgetsdup.h"
/* fopen() */
#include <stdio.h>
/* free() */
#include <stdlib.h>
/* rtrim() */
#include "rtrim.h"

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  FILE * pfile = NULL;
  char * psz = NULL;
    do {
        if (argc != 2) {
            break;
        }
        if (! (pfile = fopen(argv[1], "r"))) {
            break;
        }
        while ((psz = fgetsdup(pfile))) {
            rtrim(psz);
            fprintf(stderr, "d: %s\n", psz);
            free(psz);
            psz = NULL;
        }
        rc = 0;
    } while (0);
    if (psz) { free(psz); }
    if (pfile) { fclose(pfile); }
    return (rc);
}

    
