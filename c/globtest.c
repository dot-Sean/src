#include <stdlib.h>
#include <glob.h>
#include <stdio.h>

int
main (
  int argc,
  char * * argv ) {
  int rc = 1;
  int rcGlob;
  glob_t glob_t0;
  const char * pszPattern;
  int i;
    pszPattern = argv[1];
    rcGlob = glob(pszPattern,
     GLOB_ERR | GLOB_MARK | GLOB_NOSORT | GLOB_NOESCAPE,
     NULL, & glob_t0 );
    if (rcGlob == GLOB_NOMATCH) {
        fprintf(stderr, "Not matched.\n");
        goto exception;
    }
    if (rcGlob != 0) {
        goto exception;
    }
    for (i = 0; i < glob_t0.gl_pathc; ++ i) {
        fprintf(stdout, "%d: %s\n", i, glob_t0.gl_pathv[i]);
    }
    rc = 0;
exception:
    globfree(& glob_t0);
    return (rc);
}
