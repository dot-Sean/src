#include <stdio.h>
#include <unistd.h>
#include <signal.h>
/* exit() */
#include <stdlib.h>

void
handler () {
    exit (0);
}

int
main (
  int argc,
  char * * argv ) {
    signal(SIGALRM, handler);
    alarm(10);
    while (1) {
        fprintf(stderr, "Sleeping.\n");
        sleep(1);
    }
    return (1);
}
