#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

void
foo () {
  void * apv[128];
  int n = backtrace(apv, sizeof (apv) / sizeof (apv[0]));
  char * * ppsz;
  int i;
    backtrace_symbols_fd(apv, n, 1);
    printf("----\n");
    ppsz = backtrace_symbols(apv, n);
    for (i = 0; i < n; i ++) {
        printf("d: %s\n", ppsz[i]);
    }
    free(ppsz);
    printf("----\n");
    ppsz = backtrace_symbols(apv, n);
    for (i = 0; i < n; i ++) {
      char sz[256];
        snprintf(sz, sizeof (sz), "echo \"d: %s\"", ppsz[i]);
        system(sz);
    }
    free(ppsz);
}

int
main (
  int argc,
  char * * argv ) {
    foo();
    return (0);
}
