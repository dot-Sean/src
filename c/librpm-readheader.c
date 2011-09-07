#include <stdio.h>

#include <rpm/rpmlib.h>
#include <rpm/rpmts.h>
/* memcpy() */
#include <string.h>

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  rpmts pts = NULL; /* Transaction Set */
  FD_t pfd = NULL;
  Header pheader = NULL;
  char * pszPath = "/home/knaka/rpm/RPMS/i686/file-4.14-1.i686.rpm";
  char * psz = NULL;
  char * * ppsz = NULL;
  int iType;
  void * pv;
  int_32 nCount;
  int_32 iTag;
  int_32 aiTag[] = { RPMTAG_NAME, RPMTAG_REQUIRENAME };
  int i;
  int nNumTag = (sizeof (aiTag)) / sizeof (int_32);
    if (! (pfd = Fopen(pszPath, "r.ufdio"))) {
        fprintf(stderr, "Failed to open file.\n");
        goto except;
    }
    if (! (pts = rpmtsCreate())) {
        fprintf(stderr, "Failed to create transaction set.\n");
        goto except;
    }
    rpmtsSetVSFlags(pts, RPMVSF_NOMD5 | RPMVSF_NODSA | RPMVSF_NORSA);
    if (rpmReadPackageFile(pts, pfd, pszPath, & pheader) != RPMRC_OK) {
        fprintf(stderr, "Failed to read file.\n");
        goto except;
    }
    for (i = 0; i < nNumTag; ++ i) {
        iTag = aiTag[i];
        /* return: 1 on success, 0 on failure */
        if (headerIsEntry(pheader, iTag) == 0) {
            fprintf(stderr, "No such entry.\n");
            goto except;
        }
        /* headerGetEntryMinMemory() allocates only for the pointer
           vector of RPM_STRING_ARRAY_TYPE */
        /* return: 1 on success, 0 on failure */
        /* if (headerGetEntryMinMemory(pheader, iTag, & iType, */
        if (headerGetEntry(pheader, iTag, & iType,
         (void *) & pv, & nCount ) == 0) {
            fprintf(stderr, "Failed to get size.\n");
            goto except;
        }
        switch (iType) {
            case RPM_STRING_ARRAY_TYPE: {
              int i;
              const char * * ppszSrc = (const char * *) pv;
                ppsz = (char * *) malloc((sizeof (char *)) * (nCount + 1));
                fprintf(stderr, "d2-0: %d\n", nCount);
                for (i = 0; i < nCount; ++ i) {
                    ppsz[i] = strdup(ppszSrc[i]);
                    fprintf(stderr, "d2 (%d, %p): %s\n", i, ppsz[i], ppsz[i]);
                    /* free(ppszSrc[i]); */
                }
                ppsz[i] = NULL;
                fprintf(stderr, "d3 (%p)\n", pv);
                free(pv);
                break;
            }
            case RPM_STRING_TYPE:
            case RPM_I18NSTRING_TYPE: {
                psz = strdup(pv);
                fprintf(stderr, "d1: %s\n", psz);
                free(pv);
                break;
            }
            case RPM_BIN_TYPE: {
                /* free(pv); */
                break;
            }
            default: {
                fprintf(stderr, "Unknown type.\n");
                goto except;
            }
        }
        if (ppsz) {
          int i;
            for (i = 0; ppsz[i]; ++ i) {
                free(ppsz[i]);
            }
            free(ppsz);
            ppsz = NULL;
        }
        if (psz) {
            free(psz);
            psz = NULL;
        }
    }
    rc = 0;
except:
    if (ppsz) {
      int i;
        for (i = 0; ppsz[i]; ++ i) {
            free(ppsz[i]);
        }
        free(ppsz);
    }
    if (psz) { free(psz); }
    if (pheader) { headerFree(pheader); }
    if (pts) { rpmtsFree(pts); }
    if (pfd) { Fclose(pfd); }
    return (rc);
}
