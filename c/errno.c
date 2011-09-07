#include <stdio.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main (
  int argc,
  char * * argv ) {
  int fd;
    if ((fd = open("/hoge", O_RDONLY)) < 0) {
        perror("d");
        return (1);
    }
    return (0);
}

