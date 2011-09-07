#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

enum { BufSize = 256 };

const char * psz_ = "hoge";
const char szConst_[] = "Foo";

static char szInit_[BufSize] = "fuga";
char szUninit_[BufSize * 256];

int main() {
  FILE * pfile;
  char * psz;
    psz = (char *) malloc(BufSize * (sizeof (char)));
    printf(" code:               0x%08x\n", (int) main);
    printf(" static data:        0x%08x\n", (int) psz_);
    printf(" const data:         0x%08x\n", (int) szConst_);
    printf("--------------------------------\n");
    printf(" initialized area:   0x%08x\n", (int) szInit_);
    printf(" uninitialized area: 0x%08x\n", (int) szUninit_);
    printf("--------------------------------\n");
    printf(" heap area:          0x%08x\n", (int) psz);
    printf("--------------------------------\n");
    printf(" stack variable:     0x%08x\n", (int) pfile);
    printf("\n");
    snprintf(psz, BufSize, "/proc/%d/maps", getpid());
    pfile = fopen(psz, "r");
    while (fgets(psz, BufSize, pfile)) {
        printf(psz);
    }
    fclose(pfile);
    free((void *) psz);
    return (0);
}
