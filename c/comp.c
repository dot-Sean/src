#include <stdio.h>
#include <complex.h>

// http://seclan.dll.jp/c99d/c99d05.htm

int
main (
  int argc,
  char * * argv ) {
  double complex c1 = 2.0 - 3.0 * I;
  double complex c2 = 4.0 + 5.0 * I;
    //c1 += c2;
    c1 = c1 * c2;
    printf("%f + %f I\n", creal(c1), cimag(c1));
    printf("%f\n", cabs(c1));
    c1 = I * I;
    printf("%f + %f I\n", creal(c1), cimag(c1));
    printf("sizeof (long long int): %d\n", sizeof (long long int));
    return (0);
}
