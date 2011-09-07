#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/mount.h>

#define MAX_SECTOR_SIZE 2048

struct partition {
    unsigned char boot_ind;   /* 0x80 - active */
    unsigned char head;       /* starting head */
    unsigned char sector;     /* starting sector */
    unsigned char cyl;        /* starting cylinder */
    unsigned char sys_ind;    /* What partition type */
    unsigned char end_head;   /* end head */
    unsigned char end_sector; /* end sector */
    unsigned char end_cyl;    /* end cylinder */
    unsigned char start4[4];  /* starting sector counting from 0 */
    unsigned char size4[4];   /* nr of sectors in partition */
};

struct partition_table {
    unsigned char buffer[0x1BE];
    struct partition part[4];
    unsigned char magicflag[2];
    #define PART_TABLE_FLAG0 0x55
    #define PART_TABLE_FLAG1 0xAA
};

int
getGeometry (
  const char * pszDevice,
  int chs[3] ) {
  unsigned long lnAllSects = 0;
  struct partition_table * ptable;
  struct partition * ppart;
  int i,h,s,nHeads,nSects;
  int fFirst = 1;
  int fBad = 0;
  char mbr[MAX_SECTOR_SIZE];
  int rc = 1;
  FILE * pfile;
  int fd;
    if ((fd = open(pszDevice, O_RDONLY)) < 0) {
        fprintf(stderr, "Failed to open.\n");
        goto bye;
    }
    if ((pfile = fdopen(fd, "r")) == (void *) 0) {
        fprintf(stderr, "Failed to open.\n");
        goto close_and_bye;
    }
    if (fread(mbr, MAX_SECTOR_SIZE, 1, pfile) != 1) {
        fprintf(stderr, "Failed to read.\n");
        goto fclose_and_bye;
    }
    ptable = (struct partition_table *) mbr;
    if (
     ptable->magicflag[0] != PART_TABLE_FLAG0 ||
     ptable->magicflag[1] != PART_TABLE_FLAG1 ) {
        fprintf(stderr, "Magic not matched.\n");
        goto fclose_and_bye;
    }
    nHeads = nSects = 0;
    for (i=0; i < 4; i++) {
        ppart = & (ptable->part[i]);
        if (ppart->sys_ind != 0) {
            h = ppart->end_head + 1;
            s = (ppart->end_sector & 077);
            if (fFirst) {
                nHeads = h;
                nSects = s;
                fFirst = 0;
            } else if (nHeads != h || nSects != s)
                fBad = 1;
        }
    }

    if (! fFirst && ! fBad) {
        if (ioctl(fd, BLKGETSIZE, & lnAllSects) != 0) {
            lnAllSects = 0;
        }
        chs[1] = nHeads;
        chs[2] = nSects;
        chs[0] = lnAllSects / (nHeads * nSects);
        rc = 0;
    }
    fclose_and_bye: {
        fclose(pfile);
    }
    close_and_bye: {
        close(fd);
    }
    bye: {
        return (rc);
    }
}

int
main (
  int argc,
  char * * argv ) {
  int chs[3];
  int rc;
  const char * pszDevice;
    pszDevice = argv[1];
    rc = getGeometry(pszDevice, chs);
    if (rc == 0) {
      printf("%s: %d cylinders, %d heads, %d sectors/track\n", \
       pszDevice, chs[0], chs[1], chs[2] );
    }
    return (rc);
}
