#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main () {
  unsigned char buf0[4];
  unsigned char buf1[8];
  int n0 = 0xDEADBEEF;
  long long n1 = 0x1122334455667788LL;
    memcpy(buf0, & n0, sizeof (n0));
    memcpy(buf1, & n1, sizeof (n1));
    printf("%02x %02x %02x %02x\n", buf0[0], buf0[1], buf0[2], buf0[3]);
    printf("%02x %02x %02x %02x %02x %02x %02x %02x\n", buf1[0], buf1[1], buf1[2], buf1[3], buf1[4], buf1[5], buf1[6], buf1[7]);
    // ef be ad de
    // 88 77 66 55 44 33 22 11
    return (0);
}
