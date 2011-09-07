#include <link.h>

extern void * _dl_auxv;

int
main (
  int argc,
  char * * argv ) {
  ElfW(Dyn) * pdyn;
    for (pdyn = _DYNAMIC; pdyn->d_tag != DT_NULL; pdyn ++) {
        if (pdyn->d_tag == DT_NEEDED) {
            printf("%d\n", (size_t) pdyn->d_un.d_val);
        }
    }
    printf("_dl_auxv: %08X\n", (void *) _dl_auxv);
    return (0);
}
