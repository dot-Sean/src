#include <stdio.h>

int
main (
  int argc,
  char * * argv ) {
    fprintf(stderr, "error output\n");
    fprintf(stdout, "standard output\n");
    return (0);
}
