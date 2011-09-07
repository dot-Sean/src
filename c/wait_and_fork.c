#include <stdio.h>
#include <unistd.h>
#include <unistd.h>

int
main (
  int argc,
  char * * argv ) {
  int pid;
    printf("waiting\n");
    sleep(15);
    if ((pid = fork()) > 0) {
        printf("parent\n");
    } else if (pid == 0)  {
        printf("child\n");
    } else {
        printf("error\n");
    }
    return (0);
}
