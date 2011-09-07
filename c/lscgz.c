#include <stdio.h>
#include <zlib.h>
#include <string.h>

// cpiohdr.h in cpio
struct new_cpio_header {
    char c_magic[6];
    char c_ino[8];
    char c_mode[8];
    char c_uid[8];
    char c_gid[8];
    char c_nlink[8];
    char c_mtime[8];
    char c_filesize[8];
    char c_maj[8];
    char c_min[8];
    char c_rmaj[8];
    char c_rmin[8];
    char c_namesize[8];
    char c_chksum[8];
};

#define NEW_CPIO_MAGIC "070702"
#define NEW_CPIO_HDR_SIZE 110

int
main (
  int argc,
  char * * argv ) {
  gzFile gzfile;
  int rc = 0;
  struct new_cpio_header hdr;
    if (! (gzfile = gzopen(argv[1], "r"))) {
        rc = 1;
        fprintf(stderr, "Failed to open.\n");
        goto exit;
    }
    do {
      const char * psz;
        if (gzread(gzfile, (void *) & hdr, NEW_CPIO_HDR_SIZE) !=
         NEW_CPIO_HDR_SIZE ) {
            rc = 1;
            fprintf(stderr, "Failed to read.\n");
            goto release_and_exit;
        }
        psz = (void *) (& hdr.c_magic);
//printf("d: %s", psz);
        if (memcmp((void *) (& hdr.c_magic), NEW_CPIO_MAGIC, \
         strlen(NEW_CPIO_MAGIC) ) != 0) {
            rc = 1;
            fprintf(stderr, "Magic mismatch.\n");
            goto release_and_exit;
        }
        printf("d: %s\n", * & hdr.c_filesize);
    } while (1);
release_and_exit:
    gzclose(gzfile);
exit:
    return (rc);
}
