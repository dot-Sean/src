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
    setlocale(LC_ALL, "");
    while (fgetws(szSource, sizeof (szSource), stdin)) {
        nSrcLen = wcslen(szSource);
        while ((nMbcLen = mbrtowc(& wc, psz, nLeft, & st)) > 0) {
        //?
        //fprintf(stderr, "d:%d, %d\n", st.count, st.value);
            szBreaks[i] = '>';
            //i += nMbcLen;
            //?
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

