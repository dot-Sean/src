#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>

static dev_t getDevMajMin(const char * pszDev) {
    if (strncmp(pszDev, "sd", 2) == 0) {
        switch (pszDev[2]) {
            case ('a'): return (8 * 0x100 +  0);
            case ('b'): return (8 * 0x100 + 16);
            default: return (0);
        }
    }
    return (0);
}

int main (int argc, char * * argv) {
  char * pszDev = "sda";
  dev_t dev;
  char sz[256];
    dev = getDevMajMin(pszDev);
    snprintf(sz, sizeof (sz), "/dev/%s", pszDev);
    mknod(
    return (0);
}