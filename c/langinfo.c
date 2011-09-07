#include <stdio.h>
#include <locale.h>
#include <langinfo.h>

#if 0
void
foo (
  nl_item item ) {
    printf("%s\n", nl_langinfo(item));
}
#endif

#define foo(item) \
  printf("%16s: %s\n", #item, nl_langinfo(item));

int
main (
  int argc,
  char * * argv ) {
    setlocale(LC_ALL, "");
    foo(CODESET);
    foo(D_T_FMT);
    foo(D_FMT);
    foo(T_FMT);
    foo(DAY_6);
    foo(ABDAY_6);
    foo(MON_6);
    foo(ABMON_6);
    foo(RADIXCHAR);
    foo(THOUSEP);
    foo(YESEXPR);
    foo(NOEXPR);
    foo(CRNCYSTR);
    return (0);
}
