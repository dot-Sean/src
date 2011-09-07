#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int
main (
  int argc,
  char * * argv ) {
    mknod("/tmp/sda", S_IFBLK | 0600, makedev(0x08, 0x00));
    return (0);
}
