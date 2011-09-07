#if 0
aout=/tmp/`basename $0`.$$
${CC:-cc} $0 -o $aout && $aout; rc=$?; rm -f $aout; exit $rc
#endif

#include <stdio.h>

int
main (
  int argc,
  char * * argv ) {
    printf("Hello, world!\n");
    return (0);
}
