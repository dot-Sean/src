#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  char * pszPath = NULL;
    do {
      const char * device = "/dev/scsi/host0/bus0/target6/lun0/part1";
      const char * psz;
        pszPath = (char *) malloc((sizeof (char)) * (strlen(device) + 1));
        for (psz = device; psz; psz = strchr(psz + 1, '/')) {
            strncpy(pszPath, device, psz - device + 1);
            pszPath[psz - device + 1] = '\0';
        }
        rc = 0;
    } while (0);
    if (pszPath) { free((void *) pszPath); }
    return (rc);
}
