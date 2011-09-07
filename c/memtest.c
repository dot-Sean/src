#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define Num 10
#define Size (1024 * 1024 * 10)

int
main (
  int argc,
  char * * argv ) {
  int i;
  void * apv[Num];
  const char * pszDelim;
    while (1) {
        pszDelim = "";
        for (i = 0; i < Num; ++ i) {
            apv[i] = malloc(Size);
            bzero(apv[i], Size);
            fprintf(stderr, "%s%d", pszDelim, i); fflush(stderr);
            pszDelim = " ";
            sleep(1);
        }
        fprintf(stderr, "\n"); fflush(stderr);
        for (i = 0; i < Num; i += 2) {
            free(apv[i]);
        }
        fprintf(stderr, "Done A\n"); fflush(stderr);
        sleep(5);
        for (i = 1; i < Num; i += 2) {
            free(apv[i]);
        }
        fprintf(stderr, "Done B\n"); fflush(stderr);
        sleep(5);
    }
    return (0);
}
