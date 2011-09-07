#include <stdio.h>
#include <pwd.h>
#include <sys/types.h>

int
main (
  int argc,
  char * * argv ) {
  int uid;
  struct passwd * pw;
    uid = getuid();
    printf("d0: %d\n", uid);
    pw = getpwuid(uid);
    printf("d1: %s, %s\n", pw->pw_name, pw->pw_dir);
    return (0);
}

