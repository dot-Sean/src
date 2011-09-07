#include <stdio.h>

#include <config.h>

#include "gettext.h"

#define _(s) gettext(s)
#define N_(s) (s)

int
main (
  int argc,
  char * * argv ) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE_NAME, datadir "/locale/");
    textdomain(PACKAGE_NAME);
    printf(_("Hello, World!\n"));
    return (0);
}
