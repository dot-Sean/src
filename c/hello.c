#include <stdio.h>
#include <unistd.h>

char sz2[256];
char sz[] = "Hello World!\n";

int
main (
  int argc,
  char * * argv ) {
    while (1) {
        printf(sz);
        sleep(1);
    }
    return (0);
}

