#include <stdio.h>

int
main (
  int argc,
  char * * argv ) {
    printf("d: %08x\n", _edata);
    return 1;
}
