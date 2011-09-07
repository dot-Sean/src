#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

int
main (
  int argc,
  char * * argv ) {
  struct passwd * ppasswd;
    ppasswd = getpwnam(argv[1]);
    printf("d: %s\n", ppasswd->pw_name);
    return (0);
}
