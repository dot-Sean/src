#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int
main (
  int argc,
  char * * argv ) {
    close(0);
    close(1);
    close(2);
    while (1) {
        sleep(0x7FFFFFFF);
    }
    return (0);
}
