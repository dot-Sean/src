#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "split.h"

static char *
skipBlank (
  const char * pszArg,
  int (* isdelim) (int) ) {
  const char * psz;
    for (psz = pszArg; (* psz) && isdelim(* psz); ++ psz) { ; }
    return ((char *) psz);
}

static char *
searchBlank (
  const char * pszArg,
  int (* isdelim) (int) ) {
  const char * psz;
    for (psz = pszArg; (* psz) && (! isdelim(* psz)); ++ psz) { ; }
    return ((char *) psz);
}

int
splitEx (
  const char * pszArg,
  int nMaxTok,
  char * * ppszBuf,
  const char * * ppszTokens,
  int (* isdelim) (int) ) {
  int iNumTok = -1;
    do {
      char * psz;
        if (! ((* ppszBuf) = strdup(pszArg))) {
            break;
        }
        for (
         psz = skipBlank(* ppszBuf, isdelim), iNumTok = 0;
         (* psz) && iNumTok < nMaxTok;
         ++ iNumTok
        ) {
            ppszTokens[iNumTok] = psz;
            psz = searchBlank(psz, isdelim);
            if ((* psz) && (iNumTok + 1 < nMaxTok)) {
                ((* (psz ++)) = '\0');
            }
            psz = skipBlank(psz, isdelim);
        }
    } while (0);
    return (iNumTok);
}

int split (
  const char * pszArg,
  int nMaxTok,
  char * * ppszBuf,
  const char * * pszTokens ) {
    return (splitEx(pszArg, nMaxTok, ppszBuf, pszTokens, isspace));
}

#if 1
#include <stdio.h>
#include "strdupf.h"

static inline int
istab (
  const int c ) {
    return (c == '\t');
}

int
main (
  int argc,
  char * * argv ) {
  int rc = -1;
  const char * * ppszTokens = NULL;
  char * pszBuf = NULL;
    do {
      int nMaxTok;
      int nNumTok;
      int i;
      const char sz[] = "  hoge fuga1\t hare2 fure     foo bar bar\nzzz";
        nMaxTok = 4;
        if (! (ppszTokens =
         (const char * *) malloc((sizeof (const char *)) * nMaxTok) )) {
            break;
        }
        if ((nNumTok = split(sz, nMaxTok, & pszBuf, ppszTokens)) < 0) {
            break;
        }
        for (i = 0; i < nNumTok; ++ i) {
            printf("%d: <%s>\n", i, ppszTokens[i]);
        }
        if ((nNumTok = splitEx(sz, nMaxTok, & pszBuf, ppszTokens, istab))
         < 0 ) {
            break;
        }
        for (i = 0; i < nNumTok; ++ i) {
            printf("%d: <%s>\n", i, ppszTokens[i]);
        }
        rc = 0;
    } while (0);
    if (ppszTokens) { free(ppszTokens); }
    if (pszBuf) { free(pszBuf); }
    return (rc);
}
#endif
