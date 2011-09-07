#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <sys/mman.h>

#include <fcntl.h>

int
main (
  int argc,
  char * * argv ) {
  const char * pszFile;
  struct stat stat1;
  const char * pszMaped;
  int fd;
  int i;
    pszFile = argv[1];
    lstat(pszFile, & stat1);
    if (! S_ISREG(stat1.st_mode)) {
        fprintf(stderr, "%s is not a regular file.\n", pszFile);
        return (1);
    }
    fd = open(pszFile, O_RDONLY);
    pszMaped = (const char *) mmap((void *) 0, stat1.st_size, PROT_READ,
     MAP_SHARED, fd, (off_t) 0 );
    for (i = 0; i < stat1.st_size; i ++) {
        fputc(pszMaped[i], stdout);
    }
    munmap((void *) pszMaped, stat1.st_size);
    close(fd);
    return (0);
}

