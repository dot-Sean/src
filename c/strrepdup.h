#ifndef STRREPDUP_H
#define STRREPDUP_H

#include <stdlib.h>
#include <string.h>

static char *
strrepdup (
  const char * pszSearch,
  const char * pszReplace,
  const char * pszSubject ) {
  char * pszRet;
  const char * psz = strstr(pszSubject, pszSearch);
    if (psz) {
      size_t nPreceding = psz - pszSubject;
      size_t nSearch = strlen(pszSearch);
      size_t nReplace = strlen(pszReplace);
      size_t nFollowing = strlen(pszSubject) - nPreceding - nSearch;
        pszRet = (char *) malloc((sizeof (char)) *
         (nPreceding + nReplace + nFollowing + 1) );
        strncpy(pszRet, pszSubject, nPreceding);
        strncpy(pszRet + nPreceding, pszReplace, nReplace);
        strncpy(pszRet + nPreceding + nReplace, psz + nSearch, nFollowing);
        pszRet[nPreceding + nReplace + nFollowing] = '\0';
    } else {
        pszRet = strdup(pszSubject);
    }    
    return (pszRet);
}

#endif
