#include <math.h>
#include <stdio.h>

int main () {
  double d0;
  double d1;
    sincos(M_PI_4, & d0, & d1);
    printf("d: %f, %f\n", d0, d1);
    return (0);
}

