/* /usr/src/linux/include/linux/compiler.h(0) */

#if __GNUC__ == 2 && __GNUC_MINOR__ < 96
#define __builtin_expect(x, expected_value) (x)
#endif

#define likely(x)	__builtin_expect((x),1)
#define unlikely(x)	__builtin_expect((x),0)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main (
  int argc,
  char * * argv ) {
  int f;
  int i;
    f = atoi(argv[1]);
    for (i = 0; likely(f) && i < 0xFFFFFFF; i ++) {
        ;
    }
    return (0);
}
