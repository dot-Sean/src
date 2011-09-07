#include <stdio.h>
#include "lib/test1.h"

int
main (
  int argc,
  char * * argv ) {
    foo(256);
    bar(argv[1]);
    return (0);
}

