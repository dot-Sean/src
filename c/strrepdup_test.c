#include "strrepdup.h"

#include <stdio.h>

int
main (
  int argc,
  char * * argv ) {
  char * psz = NULL;
    psz = strrepdup("http//", "http://", "http//ftp");
    fprintf(stderr, "d: %s\n", psz);
    if (psz) { free(psz); }
    return (0);
}
