#include <stdio.h>

#include <sys/types.h>
#include <dirent.h>

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  DIR * pdir = NULL;
    do {
      struct dirent * pdirent;
        if (argc != 2) {
            break;
        }
        if (! (pdir = opendir(argv[1]))) {
            break;
        }
        while ((pdirent = readdir(pdir))) {
            printf("d0: %s\n", pdirent->d_name);
            #if defined(_DIRENT_HAVE_D_TYPE)
            printf("d1: %d\n", pdirent->d_type);
            #endif
        }
        rc = 0;
    } while (0);
    if (pdir) { closedir(pdir); }
    return (rc);
}
