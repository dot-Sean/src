#include <stdio.h>

int
main (
  int argc,
  char * * argv ) {
  char sz[10];
  char sz1[10];
  int n;
    sscanf("             hoge", "%[ ] %s", sz1, sz);
    printf("d: %s\n", sz);
    return (0);
}
