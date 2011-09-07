#include <stdio.h>

int contains3 (int n) {
    while (n != 0) {
        if (n % 10 == 3) {
            return (1);
        }
        n = n / 10;
    }
    return (0);   
}

int
main (
  int argc,
  char * * argv ) {
  int i;
    for (i = 0; i < 20; ++ i) {
        if (i % 3 == 0 || contains3(i)) {
            printf("d: %d\n", i);
        }
    }
    return (0);
}
