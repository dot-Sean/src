#include <stdio.h>

#include <glib.h>

int
main (
  int argc,
  char * * argv ) {
  GString * pstr;
  gchar * * ppsz;
  void * apv[3];
    pstr = g_string_new("hoge,");
    g_string_append(pstr, "fuga");
    g_string_append_c(pstr, ',');
    g_string_prepend_c(pstr, ',');
    g_string_prepend(pstr, "FUGA");
    g_string_sprintfa(pstr, "%d,%s", 256, "HOGE");
    printf("%s\n", pstr->str);
    ppsz = (gchar * *) apv;
    ppsz = g_strsplit(pstr->str, ",", 3);
    for (; (* ppsz); ppsz ++) {
        printf("d: %s\n", (* ppsz));
    }
    printf("%s\n", pstr->str);
    g_string_sprintf(pstr, "%d,%s", 512, "Foo Bar");
    printf("%s\n", pstr->str);
    g_string_free(pstr, 1);
    return (0);
}
