#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <time.h>

#define ShowBit(bit) \
   if ((mode & bit) == bit) { \
        printf("%s" # bit, pszDelim); \
        pszDelim = ", "; \
    }

void
showMode (
  mode_t mode ) {
  const char * pszDelim = "";
    ShowBit(S_IFMT  );
    ShowBit(S_IFSOCK);
    ShowBit(S_IFLNK );
    ShowBit(S_IFREG );
    ShowBit(S_IFBLK );
    ShowBit(S_IFDIR );
    ShowBit(S_IFCHR );
    ShowBit(S_IFIFO );
    ShowBit(S_ISUID );
    ShowBit(S_ISGID );
    ShowBit(S_ISVTX );
    ShowBit(S_IRWXU );
    ShowBit(S_IRUSR );
    ShowBit(S_IWUSR );
    ShowBit(S_IXUSR );
    ShowBit(S_IRWXG );
    ShowBit(S_IRGRP );
    ShowBit(S_IWGRP );
    ShowBit(S_IXGRP );
    ShowBit(S_IRWXO );
}

int
main (
  int argc,
  char * * argv ) {
  const char * pszFile;
  struct stat stat1;
    pszFile = argv[1];
    if (lstat(pszFile, & stat1) != 0) {
        fprintf(stderr, "lstat failed\n");
        return (1);
    }
    printf("st_dev: %04x\n", (int) (dev_t) stat1.st_dev);
    printf("st_ino: %d\n", (int) (ino_t) stat1.st_ino);
    printf("st_mode: "); showMode((mode_t) stat1.st_mode); printf("\n");
    printf("st_nlink: %d\n", (int) (nlink_t) stat1.st_nlink);
    printf("st_uid: %d\n", (int) (uid_t) stat1.st_uid);
    printf("st_gid: %d\n", (int) (gid_t) stat1.st_gid);
    printf("st_rdev(%d): %04x\n", sizeof (dev_t), (int) (dev_t) stat1.st_rdev);
    printf("st_size(%d): %d\n", sizeof (off_t), (int) (off_t) stat1.st_size);
    printf("st_blksize: %ld\n", (unsigned long) stat1.st_blksize);
    printf("st_blocks: %ld\n", (unsigned long) stat1.st_blocks);
    printf("st_atime: %s %d\n", ctime((time_t *) & stat1.st_atime), (int) stat1.st_atime);
    printf("st_mtime: %s", ctime((time_t *) & stat1.st_mtime));
    printf("st_ctime: %s", ctime((time_t *) & stat1.st_ctime));

    return (0);
}

