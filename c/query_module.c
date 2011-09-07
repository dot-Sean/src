#include <stdio.h>
#include <linux/module.h>

int
main (
  int argc,
  char * * argv ) {
    printf("d: %d\n", query_module((void *) 0, 0, (void *) 0, 0));
    return (0);
}
