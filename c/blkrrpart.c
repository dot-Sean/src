#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* open() */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* ioctl() */
#include <sys/ioctl.h>

#include <linux/types.h>
#include <asm/types.h>
#ifndef pgoff_t
#define pgoff_t unsigned long
#endif
#include <linux/fs.h>

#define BufSize 256

int
blkrrpartAll () {
  int rc = -1;
  FILE * pfile = NULL;
  int fd = 0;
  char sz[BufSize];
  char szPath[BufSize];
    pfile = popen("awk '{ print $4 }' /proc/partitions", "r");
    if (! pfile) {
        goto except;
    }
    while (fgets(sz, sizeof (sz), pfile)) {
        if ((strlen(sz) > 0) && (sz[strlen(sz) - 1] == '\n')) {
            sz[strlen(sz) - 1] = '\0';
        }
        if (strlen(sz) == 0) {
            goto loop_except;
        }
        snprintf(szPath, sizeof (szPath), "/dev/%s", sz);
        if (access(szPath, R_OK) != 0) {
            goto loop_except;
        }
        fd = open(szPath, O_RDWR);
        if (! fd) {
            goto loop_except;
        }
        if (ioctl(fd, BLKRRPART) != 0) {
            goto loop_except;
        }
loop_except:
        if (fd) {
            close(fd);
            fd = 0;
        }
    }
    rc = 0;
except:
    if (pfile) { pclose(pfile); }
    return (rc);
}

int
main (
  int argc,
  char * * argv ) {
    blkrrpartAll();
    return (0);
}
