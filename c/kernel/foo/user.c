#include <stdio.h> /* printf(3) */
#include <stdlib.h> /* exit(3) */
#include <string.h> /* memset(3) */
#include <sys/types.h> /* read(2) */
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h> /* errno */

#include "foo_ioctl.h"

static const char * devfile = "/dev/foo3";

void
read_buffer (
  int fd ) {
  unsigned char buf[64];
  int ret;
  int i;
    ret = read(fd, buf, sizeof (buf));
    if (ret == -1) {
        perror("read");
    }
    for (i = 0; i < ret; i ++) {
        printf("%02x ", buf[i]);
        if (i % 16 == 15) {
            printf("\n");
        }
    }
    printf("\n");
}

int
main (
  int argc,
  char * * argv ) {
  struct foo_ioctl_arg iocarg;
  int ret;
  int fd;
    fd = open(devfile, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    memset(& iocarg, 0, sizeof (iocarg));
    ret = ioctl(fd, IOCTL_VALGET, & iocarg);
    if (ret == -1) {
        printf("errno 0: %d\n", errno);
        perror("ioctl");
    }
    printf("val: %02x\n", iocarg.val);
    read_buffer(fd);
    memset(& iocarg, 0, sizeof (iocarg));
    iocarg.val = 0xCC;
    ret = ioctl(fd, IOCTL_VALSET, & iocarg);
    if (ret == -1) {
        printf("errno 1: %d\n", errno);
        perror("ioctl");
    }
    read_buffer(fd);
    memset(& iocarg, 0, sizeof (iocarg));
    ret = ioctl(fd, IOCTL_VALGET, & iocarg);
    if (ret == -1) {
        printf("errno 2: %d\n", errno);
        perror("ioctl");
    }
    printf("val: %02x\n", iocarg.val);
    close(fd);
    return (0);
}
