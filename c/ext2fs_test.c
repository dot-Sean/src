#include <stdio.h>
#include <ext2fs/ext2fs.h>

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  ext2_filsys pfs = NULL;
  char * pszDev;
    if (argc < 2) {
        goto exception;
    }
    pszDev = argv[1];
    if (ext2fs_open(pszDev, EXT2_FLAG_FORCE, 0, 0,
     unix_io_manager, & pfs ) != 0) {
        goto exception;
    }
    fprintf(stderr, "LABEL: %s\n", pfs->super->s_volume_name);
    fprintf(stderr, "last mounted: %s\n", pfs->super->s_last_mounted);
    {
      int i;
        fprintf(stderr, "UUID: ");
        for (i = 0; i < 16; i ++) {
            fprintf(stderr, "%02X", pfs->super->s_uuid[i]);
        }
        fprintf(stderr, "\n");
    }
    rc = 0;
exception:
    if (pfs) { ext2fs_close(pfs); }
    return (rc);
}
