#include <stdio.h>
#include <parted/parted.h>

int
main (
  int argc,
  char * * argv ) {
    //ped_init();
    fprintf(stderr, "d0: %p\n", ped_file_system_type_get("ext2"));
    fprintf(stderr, "d1: %p\n", ped_file_system_type_get("linux-swap"));
    return (0);
}
