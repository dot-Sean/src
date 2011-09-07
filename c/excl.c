/* shippai */

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int
main (
  int argc,
  char * * argv ) {
  int iFd;
  pid_t pid;
  FILE * pfile;
  int i;
  char sz[256];
    pid = getpid();
    iFd = open(argv[1], O_RDWR);
    if (iFd < 0) {
        snprintf(sz, sizeof (sz), "%d: open() failed", pid);
        perror(sz);
        exit(1);
    }
    if (flock(iFd, LOCK_EX | LOCK_NB) != 0) {
        snprintf(sz, sizeof (sz), "%d: flock() failed", pid);
        perror(sz);
        exit(1);
    }
    pfile = fdopen(iFd, "r+");
    if (! pfile) {
        snprintf(sz, sizeof (sz), "%d: fdopen() failed", pid);
        perror(sz);
        exit(1);
    }
    for (i = 0; i < 10; i ++) {
        fprintf(pfile, "%d: %d\n", pid, i);
        fflush(pfile);
        sleep(1);
    }
    if (flock(iFd, LOCK_UN) != 0) {
        snprintf(sz, sizeof (sz), "%d: flock() failed", pid);
        perror(sz);
        exit(1);
    }
    fclose(pfile);
    return (0);
}

