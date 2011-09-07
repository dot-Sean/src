

#define BufSize 4096

#include <wchar.h>

#include <locale.h>

#include <stdio.h>
#include <string.h>

int
main (
  int argc,
  char * * argv ) {
  wchar_t szSource[BufSize];
  wchar_t szBreaks[BufSize];
  int nSrcLen;
  int i;
  int nLeft;
  wchar_t * psz;
  int nMbcLen;
  wchar_t wc;
  mbstate_t st;
    setlocale(LC_ALL, "");
    while (fgetws(szSource, sizeof (szSource), stdin)) {
        nSrcLen = wcslen(szSource);
        szBreaks[nSrcLen] = '\0';
        if (szSource[nSrcLen - 1] == '\n') {
            nSrcLen --;
        }
        memset((void *) szBreaks, (int) '.', nSrcLen);
        psz = szSource;
        nLeft = nSrcLen;
        i = 0;
        while ((nMbcLen = mbrtowc(& wc, psz, nLeft, & st)) > 0) {
            szBreaks[i] = '>';
            i += wcwidth(wc);
            nLeft -= nMbcLen;
            psz += nMbcLen;
        }
        szBreaks[nSrcLen] = '\n';
        fprintf(stdout, "%s", szSource);
        fprintf(stdout, "%s", szBreaks);
    }
    return (0);
}

