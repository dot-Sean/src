#include <stdio.h>
#include <unistd.h>
#include <newt.h>
#include <distro.h>

int
main (
  int argc,
  char * * argv ) {
  char sz[256];
  int rc;
  newtComponent form;
    newtInit(); // {
    newtCls();
    snprintf(sz, sizeof (sz), "Welcome to %s", getdistro(DISTRO_DISTRIBUTION));
    newtDrawRootText(0, 0, sz);
    newtPushHelpLine(" <Tab>/<Alt-Tab> between elements | <Space> selects "
     "| <F12> next screen       " );
    form = newtForm(NULL, NULL, 0);
    newtDrawForm(form);
    newtRefresh();
    newtFormDestroy(form);
    rc = newtWinChoice("hoge", "ok", "cancel", "Hello");
    newtFinished(); // }
    return (0);
}
