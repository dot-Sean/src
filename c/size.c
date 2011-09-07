#include <stdio.h>

int
main (
  int argc,
  char * * argv ) {
    printf("d0: %d\n", sizeof(char));
    printf("d1: %d\n", sizeof(int));
    printf("d2: %d\n", sizeof(long double));
    return (0);
}
