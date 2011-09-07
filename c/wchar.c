// 蜜柑

#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>

int
main (
  int argc,
  char * * argv ) {
  char * ac;
  size_t i;
  wchar_t wc;
  mbstate_t mbstat;
  char * pszSrc;
    pszSrc = argv[1];
    ac = (char *) malloc(MB_CUR_MAX);
    setlocale(LC_ALL, "");
printf("d0: %s\n", pszSrc);
    while (* pszSrc) {
        memset(ac, '\0', MB_CUR_MAX);
        memset(& mbstat, '\0', sizeof (mbstate_t));
        for (i = 0; i < MB_CUR_MAX; i ++) {
          size_t sizeRet;
            ac[i] = (* (pszSrc ++));
            sizeRet = mbrtowc(& wc, ac, i, & mbstat); 
printf("d1: %d\n", (int) sizeRet);
            if (sizeRet > 0) {
                break;
            } else if (sizeRet == (size_t) -2) {
                memset(& mbstat, '\0', sizeof (mbstate_t));
                /* ワイド文字に変換するにはバイトが足りない */
            } else if (sizeRet == (size_t) -1) {
                /* ワイド文字に変換できなかった */
                exit(1);
            }
        }
        fwprintf(stdout, "d3: %c", wc);
    }
    return (0);
}
