#include <stdio.h>

#include <string.h>

#include <locale.h>

#include <wchar.h>
#include <wctype.h>

int
main (
  int argc,
  char * * argv ) {
  int nLength;
  int nWidth;
  wchar_t wc;
  mbstate_t mbs;
    setlocale(LC_ALL, "");
    memset(& mbs, 0, sizeof (mbstate_t));
    nLength = mbrtowc(& wc, argv[1], strlen(argv[1]), & mbs);
printf("d0: %d\n", nLength);
    nWidth = wcwidth(wc);
printf("d1: %d\n", nWidth);
    return (0);
}

