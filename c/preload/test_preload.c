#include <stdio.h>
#include <string.h>

int
main (
  int argc,
  char * * argv ) {
    printf("printf()\n");
    puts("puts()");
    fputs("fputs()\n", stdout);
    fflush(stdout);
#define s "write()\n"
    write(1, s, strlen(s));
    return (0);
}
