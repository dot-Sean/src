/* NULL */
#include <stdlib.h>
/* listxattr() */
#include <sys/types.h>
#include <attr/xattr.h>
/* fprintf() */
#include <stdio.h>

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  char * psz = NULL;
    do {
      static int sizeSz = 256;
      int n;
        psz = malloc((sizeof (char)) * sizeSz);
        if ((n = listxattr("/bin/bash", psz, sizeSz)) < 0) {
            break;
        }
        fprintf(stderr, "d0: %d\n", n);
        fprintf(stderr, "d1: %s\n", psz);
        rc = 0;
    } while (0);
    if (psz) { free(psz); }
    return (rc);
}
