#include <stdio.h>
/* mkstemp() */
#include <stdlib.h>
/* close() */
#include <unistd.h>

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  int fd = -1;
  char szFile[] = "/tmp/hogeXXXXXX";
  FILE * pfile = NULL;
    do {
        if ((fd = mkstemp(szFile)) < 0) {
            break;
        }
        if (! (pfile = fdopen(fd, "w"))) {
            break;
        } else {
            fd = -1;
        }
        fprintf(pfile, "Hello\n");
        fprintf(pfile, "World\n");
        rc = 0;
    } while (0);
    if (pfile || fd >= 0) {
        if (pfile) { fclose(pfile); }
        if (fd >= 0) { close(fd); }
        unlink(szFile);
    }
    return (rc);
}
