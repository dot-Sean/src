#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include "fgetsdup.h"
#include "trim.h"

#define MaxNumInterface 16

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  /* dynamic */
  int fd = -1;
    do {
      struct ifreq aifreq[MaxNumInterface];
      int i;
      int n;
      int fUseIfconf = 0;
        if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            fprintf(stderr, "Failed to open socket.\n");
            break;
        }
        /* SIOCGIFCONF enumelates only the interfaces which have IP
           addresses */
        if (fUseIfconf) {
          struct ifconf ifconf0;
            ifconf0.ifc_len = sizeof (aifreq);
            ifconf0.ifc_ifcu.ifcu_buf = (void *) aifreq;
            if (ioctl(fd, SIOCGIFCONF, & ifconf0) != 0) {
                fprintf(stderr, "Failed to get interface configuration.\n");
                break;
            }
            n = ifconf0.ifc_len / sizeof (struct ifreq);
        } else {
          FILE * pfile;
          char * pszHead;
          char * psz;
            if (! (pfile = fopen("/proc/net/dev", "r"))) {
                fprintf(stderr, "Failed to open /proc/net/dev.\n");
                break;
            }
            for (
             i = 0;
             i < MaxNumInterface && (psz = pszHead = fgetsdup(pfile));
             free(pszHead) ) {
              /* IP aliases do not appear in the file */
              char * pszColon = strchr(psz, ':');
                if (! pszColon) {
                    continue;
                }
                (* pszColon) = '\0';
                trim(psz);
                strncpy(aifreq[i ++].ifr_name, psz, IFNAMSIZ);
            }
            fclose(pfile);
            n = i;
        }
        for (i = 0; i < n; ++ i) {
          struct sockaddr * psockaddr;
            aifreq[i].ifr_addr.sa_family = AF_INET;
            if (ioctl(fd, SIOCGIFHWADDR, aifreq + i) != 0) {
                continue;
            }
            psockaddr = & (aifreq[i].ifr_hwaddr);
            printf("%s (%.2X:%.2X:%.2X:%.2X:%.2X:%.2X)\n",
             aifreq[i].ifr_name,
             (unsigned char) psockaddr->sa_data[0],
             (unsigned char) psockaddr->sa_data[1],
             (unsigned char) psockaddr->sa_data[2],
             (unsigned char) psockaddr->sa_data[3],
             (unsigned char) psockaddr->sa_data[4],
             (unsigned char) psockaddr->sa_data[5] );
        }
        rc = 0;
    } while (0);
    if (fd > 0) { close(fd); }
    return (rc);
}
