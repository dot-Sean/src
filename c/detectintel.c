#include <stdio.h>

#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <unistd.h>

unsigned short int
getWord (
  const unsigned char * pb,
  unsigned int iPos ) {
    return (pb[iPos] | (pb[iPos + 1] << 8));
}

#define PciStandardizedLength 64
#define PciVendorId 0x00
#define PciDeviceClass 0x0A

#define PciVendorIntel ((unsigned short int) 0x8086)
#define PciClassBridgeHost ((unsigned short int) 0x0600)

int
detect () {
  DIR * pdir0;
  DIR * pdir1;
  struct dirent * pdirent0;
  struct dirent * pdirent1;
  char sz[64];
  const char ab[PciStandardizedLength];
  int fd;
  int found = 0;
    if ((pdir0 = opendir("/proc/bus/pci/"))) {
        while ((pdirent0 = readdir(pdir0)) != (void *) 0) {
            if (pdirent0->d_name[0] != '.') {
                snprintf(sz, sizeof (sz), "/proc/bus/pci/%s",
                 pdirent0->d_name );
                if ((pdir1 = opendir(sz))) {
                    while (pdir1 &&
                     (pdirent1 = readdir(pdir1)) != (void *) 0 ) {
                        if (pdirent1->d_name[0] != 0) {
                            snprintf(sz, sizeof (sz), "/proc/bus/pci/%s/%s",
                             pdirent0->d_name, pdirent1->d_name );
                            if ((fd = open(sz, O_RDONLY))) {
                                read(fd, (void *) ab, PciStandardizedLength);
                                if (
                                 (getWord(ab, PciVendorId) ==
                                  PciVendorIntel ) &&
                                 (getWord(ab, PciDeviceClass) ==
                                  PciClassBridgeHost )) {
                                    found = 1;
                                }
                                close(fd);
                            }
                        }
                    }
                    closedir(pdir1);
                }
            }
        }
        closedir(pdir0);
    }
    return (found);
}

int
main (
  int argc,
  char * * argv ) {
    printf("result: %d\n", detect());
    return (0);
}
