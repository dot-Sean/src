/* NULL */
#include <stdlib.h>
/* fprintf() */
#include <stdio.h>
/* readdir() */
#include <dirent.h>
/* S_SIDIR() */
#include <sys/stat.h>
/* strcmp() */
#include <string.h>
/* strdupf() */
#include "strdupf.h"

#define NumIndentColumns 2

#define CurDirName "."
#define ParDirName ".."

static int
dirtree (
  const char * pszDir,
  int nDepth ) {
  int rc = -1;
  DIR * pdir = NULL;
  char * pszSubDir = NULL;
  struct dirent * pdirent;
  int i;
    if (! (pdir = opendir(pszDir))) {
        for (i = 0; i < nDepth; ++ i) { fprintf(stderr, " "); }
        fprintf(stderr, "Failed to open directory \"%s\".\n", pszDir);
        /* does not stop */
        rc = 0;
        goto exception;
    }
    while ((pdirent = readdir(pdir))) {
        if (
         strcmp(pdirent->d_name, CurDirName) == 0 ||
         strcmp(pdirent->d_name, ParDirName) == 0 ) {
            continue;
        }
        for (i = 0; i < nDepth; ++ i) { fprintf(stderr, " "); }
        fprintf(stderr, "%s%s\n", pdirent->d_name,
         S_ISDIR(DTTOIF(pdirent->d_type))? "/": "" );
        if (S_ISDIR(DTTOIF(pdirent->d_type))) {
            if (! (pszSubDir =
             strdupf("%s/%s", pszDir, pdirent->d_name) )) {
                goto exception;
            }
            if (dirtree(pszSubDir, nDepth + NumIndentColumns) != 0) {
                goto exception;
            }
            free(pszSubDir);
            pszSubDir = NULL;
        }
    }
    rc = 0;
exception:
    if (pszSubDir) { free(pszSubDir); }
    if (pdir) { closedir(pdir); }
    return (rc);
}

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
    do {
        if (argc != 2) {
            break;
        }
        if (dirtree(argv[1], 0) != 0) {
            break;
        }
        rc = 0;
    } while (0);
    return (rc);
}
