#include <stdio.h>

int
main (
  int argc,
  char * * argv ) {
    printf("d: %d\n", strcmp(argv[1], argv[2]));
    return (0);
}
