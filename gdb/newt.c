
#include <stdio.h>
#include <newt.h>

static void
foo (
  const char * psz ) {
  int i;
  int n;
    for (i = 0; i < 10; i ++) {
        n = i;
    }
    newtWinMessage("Title", "Button", (char *) psz);
}

int
main (
  int argc,
  char * * argv ) {
    newtInit();
    foo("Message");
    newtFinished();
    return (0);
}
