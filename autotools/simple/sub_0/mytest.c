#include <stdio.h>

#include <mylib.h>

int
main (
  int argc,
  char * *  argv ) {
    fprintf(stderr, "In executable.\n");
    myfunc();
    return (0);
}
