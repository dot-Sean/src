#include <sys/types.h>

#ifndef uint8_t
#  define uint8_t	unsigned char
#endif
#ifndef uint16_t
#  define uint16_t	unsigned short int
#endif
#ifndef uint32_t
#  define uint32_t	unsigned int
#endif
#ifndef uint64_t
#  define uint64_t	unsigned long long int
#endif

#include <linux/lvm.h>

int vg_status (char * vg_name, vg_t * * vg);

#include <stdio.h>

char * cmd = (void *) 0;
int opt_d = 0;

int
main (
  int argc,
  char * * argv ) {
  vg_t * pvg = (void *) 0;
  int ret;
    ret = vg_status(argv[1], & pvg);
    printf("d0: %d\n", ret);
    return (0);
}
