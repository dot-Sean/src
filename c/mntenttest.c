#include <stdio.h>
/* setmntent() */
#include <mntent.h>
/* statvfs() */
#include <sys/statvfs.h>
/* access() */
#include <unistd.h>

int
main (
  int argc,
  char * * argv ) {                
  int rc = -1;
  FILE * pfile = NULL;
    do {
      struct mntent * pmntent;
      const char * pszStatfile;
      struct statvfs fsd;
        if (! (pfile = setmntent("/proc/mounts", "r"))) {
            break;
        }
	while ((pmntent = getmntent(pfile)) != NULL) {
            if (access(pmntent->mnt_dir, R_OK) == 0) {
                pszStatfile = pmntent->mnt_dir;
            } else {
                pszStatfile = pmntent->mnt_fsname;
            }
	    fprintf(stderr, "d:%s (%d)\n", pmntent->mnt_fsname,
	     statvfs(pszStatfile, & fsd) );
	}

	rc = 0;
    } while (0);
    if (pfile) { endmntent(pfile); }
    return (rc);
}    

