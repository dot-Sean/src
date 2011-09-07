#include <stdio.h>
#include <dlfcn.h>

int
main (
  int argc,
  char * * argv ) {
    _dlinfo();
    return (0);
}