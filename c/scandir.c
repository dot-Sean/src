/* scandir() */
#include <dirent.h>
/* NULL */
#include <stdlib.h>
/* fprintf() */
#include <stdio.h>
/* strcmp() */
#include <string.h>

int
isTarget (
  const struct dirent * pdirent ) {
    return (strstr(pdirent->d_name, "ta") != NULL);
}

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  struct dirent * * ppdirent = NULL;
  int i;
  int n;
    for (
     i = 0;
     i < (n = scandir("/etc/", & ppdirent, isTarget, NULL));
     ++ i ) {
        fprintf(stderr, "d: %s\n", ppdirent[i]->d_name);
    }
    rc = 0;
exception:
    if (n > 0) {
        for (i = 0; i < n; ++ i) { free(ppdirent[i]); }
        free(ppdirent);
    }
    return (rc);
}
