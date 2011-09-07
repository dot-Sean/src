#include <stdio.h> /* printf(3) */
#include <stdlib.h> /* exit(3) */

#include <sys/types.h> /* O_RDWR */
#include <sys/stat.h>
#include <fcntl.h>

#include <poll.h> /* poll() */

static const char * devfile = "/dev/bar0";

int
main (
  int argc,
  char * * argv ) {
  int fd;
  struct pollfd fds;
  int retval;
  unsigned char buf[64];
  ssize_t size;
  int i;
    fd = open(devfile, O_RDWR);
    if (fd == -1) {
        perror("open");
        goto error;
    }
    do {
        fds.fd = fd;
        fds.events = POLLIN;
        printf("poll() ...\n");
        retval = poll(& fds, 1, 5 * 1000);
        if (retval == -1) {
            perror("poll");
            break;
        }
        if (retval) {
            break;
        }
    } while (retval == 0);
    if (fds.revents & POLLIN) {
        printf("read() ...\n");
        size = read(fd, buf, sizeof (buf));
        printf("read() %d\n", size);
        for (i = 0; i < size; i ++) {
            printf("%02x ", buf[i]);
        }
        printf("\n");
    }
error:
    close(fd);
    return (0);
}
