#include <stdio.h>

#include <glib.h>

static void
func (
  gpointer data,
  gpointer user_data ) {
    printf("d1: %s\n", (const char *) data);
}

static gint
comp (
  gconstpointer a,
  gconstpointer b ) {
    return (strcmp((const char *) a, (const char *) b));
}

int
main (
  int argc,
  char * * argv ) {
  GList * plistTop = (void *) 0;
  char * pszRemoved = "removed";
  int i;
  int n;
    plistTop = g_list_append(plistTop, (gpointer) "hoge");
    plistTop = g_list_prepend(plistTop, (gpointer) "fuga");
    plistTop = g_list_prepend(plistTop, (gpointer) "bar");
    plistTop = g_list_prepend(plistTop, (gpointer) "foo");
    plistTop = g_list_append(plistTop, (gpointer) pszRemoved);
    plistTop = g_list_remove(plistTop, (gpointer) pszRemoved);
    n = g_list_length(plistTop);
    printf("d0: %d\n", n);
    printf("\n");
    for (i = 0; i < n; i ++) {
        printf("d1: %s\n", (const char *) g_list_nth_data(plistTop, i));
    }
    printf("\n");
    plistTop = g_list_sort(plistTop, comp);
    g_list_foreach(plistTop, func, (void *) 0);
    printf("\n");
    plistTop = g_list_insert_sorted(plistTop, (gpointer) "goo", comp);
    {
      GList * plist;
        for (plist = plistTop; plist;  plist = g_list_next(plist)) {
            printf("d2: %s\n", (const char *) plist->data);
        }
    }
    g_list_free(plistTop);
    return (0);
}

