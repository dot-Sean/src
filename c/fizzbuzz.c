#include <stdio.h>
/* strlen() */
#include <string.h> 

const char * Fizz = "Fizz";
const char * Buzz = "Buzz";
const int Num = 100;

static void
doFizzBuzz0 () {
  int i;
  char sz[strlen(Fizz) + strlen(Buzz) + 1];
    for (i = 1; i <= Num; ++ i) {
        sz[0] = '\0';
        if ((i / 3) * 3 == i) { strcat(sz, Fizz); }
        if ((i / 5) * 5 == i) { strcat(sz, Buzz); }
        if (strlen(sz) == 0) { snprintf(sz, sizeof (sz), "%d", i); }
        fprintf(stdout, "%s\n", sz);
    }
}

static void
doFizzBuzz1 () {
  int i;
    for (i = 0; i <= Num; ++ i) {
      int n = 0;
        if ((i % 3) == 0) { n += fprintf(stdout, Fizz); }
        if ((i % 5) == 0) { n += fprintf(stdout, Buzz); }
        if (n == 0) { fprintf(stdout, "%d", i); }
        fputs("\n", stdout);
    }
}

static void
doFizzBuzz2 () {
  int i;
    for (i = 0; i <= Num; ++ i) {
        if (0 == fprintf(stdout, "%s%s", 
         ((i % 3) == 0)? Fizz: "", 
         ((i % 5) == 0)? Buzz: "" )) {
            fprintf(stdout, "%d", i);
        }
        fputs("\n", stdout);
    }
}

int
main (
  int argc,
  char * * argv ) {
    doFizzBuzz0();
    doFizzBuzz1();
    doFizzBuzz2();
    return (0);
}
