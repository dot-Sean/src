#include <stdio.h>

#include "strdupf.h"

int
main (
  int argc,
  char * * argv ) {
  char * psz;
    psz = strdupf("%s - %s - %s, %d\n", "hoge", "fuga", "foo", 256);
    fprintf(stderr, psz);
    return (0);
}
