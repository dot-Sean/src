// http://www.findterry.com/projects.cgi?project=exception

#include <stdio.h>
#include "exception.h"

static void
foo (
  int i ) {
    printf("d: %d\n", 100 / i);
}

int
main (
  int argc,
  char * * argv ) {
  int i;
    init_exception_handler(argv[0]);
    for (i = -3; i < 3; i ++) {
      int e;
        try {
            foo(i);
            throw(UnknownException);
        } catch (e) {
            e_getMessage(e, __func__);
            printStackTrace();
        }
    }
    return (0);
}
