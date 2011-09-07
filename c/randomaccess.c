#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>

#include <time.h>

int
main (
  int argc,
  char * * argv ) {
  int fd;
  char ac[512];
  int i;
  off_t offset;
    fd = open("/dev/sda", O_RDONLY);
    srand(time(NULL));
    for (i = 0; i < 1000; i ++) {
        // #define RAND_MAX 2147483647
        //offset = (rand() % 1953520060) * 512;
        offset = i * 512;
        printf("%lld ", offset);
        lseek(fd, offset, SEEK_SET);
        read(fd, ac, sizeof (ac));
        //write(1, ac, sizeof (ac));
        //printf("d");
    }
    return (0);
}