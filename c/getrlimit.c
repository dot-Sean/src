#include <stdio.h>

#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

int
main (
  int argc,
  char * * argv ) {
  struct rlimit rlim;
    getrlimit(RLIMIT_FSIZE, & rlim);
    printf("d: %d, %d", rlim.rlim_cur, rlim.rlim_max);
    return (0);
}
