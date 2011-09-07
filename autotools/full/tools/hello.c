#include <hello.h>
#include <stdio.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

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
    hello();
    fprintf(stderr, "%s\n", _("World"));
    return (0);
}
