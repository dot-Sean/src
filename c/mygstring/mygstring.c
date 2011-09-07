#include <glib.h>
#include <glib-object.h>

typedef struct MyString_ {
    GObject object;
} MyString;

typedef struct MyStringClass_ {
    GObjectClass object_class;
} MyStringClass;

G_DEFINE_TYPE(MyString, my_string, G_TYPE_OBJECT);

#define G_DEFINE_MISC(MyString, my_string, MY_STRING) \
 GType 


/* GObject type identifier */
#define TYPE_MY_STRING (my_string_get_type())

/* Cast instance */
#define MY_STRING(obj) \
 (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_MY_STRING, MyString))

/* Cast class */
#define MY_STRING_CLASS(klass) \
 (G_TYPE_CHECK_CLASS_CAST((klass), TYPE_MY_STRING, MyStringClass))

/* Check instance */
#define IS_MY_STRING(obj) \
 (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_MY_STRING))

/* Check class */
#define IS_MY_STRING_CLASS(klass) \
 (G_TYPE_CHECK_CLASS_TYPE((klass), TYPE_MY_STRING))

/* Instance to class */
#define MY_STRING_GET_CLASS(obj) \
 (G_TYPE_INSTANCE_GET_CLASS((obj), TYPE_MY_STRING, MyStringClass))


/* ---------------------------------------------------------------- */

#include <stdio.h>

static void
my_string_dispose (
  GObject * self ) {
    fprintf(stderr, "%s\n", __func__);
    G_OBJECT_CLASS(my_string_parent_class)->dispose(self);
}

static void
my_string_finalize (
  GObject * self ) {
    fprintf(stderr, "%s\n", __func__);
    G_OBJECT_CLASS(my_string_parent_class)->finalize(self);
}

static void
my_string_class_init (
  MyStringClass * pclass ) {
  GObjectClass * pobjectclass = (GObjectClass *) pclass;
    fprintf(stderr, "%s\n", __func__);
    // http://www.gnome.gr.jp/docs/glib-2.8.x-refs/gobject/gobject-memory.html#gobject-destruction-table
    pobjectclass->dispose = my_string_dispose;
    pobjectclass->finalize = my_string_finalize;
}

static void
my_string_init (
  MyString * self ) {
    fprintf(stderr, "%s\n", __func__);
}

/* ---------------------------------------------------------------- */

#include <glib.h>
//#include "mystring.h"

typedef struct LimitedString_ {
    MyString object;
} LimitedString;

typedef struct LimitedStringClass_ {
   MyStringClass object_class;
} LimitedStringClass;

G_DEFINE_TYPE(LimitedString, limited_string, TYPE_MY_STRING);

/* GObject type identifier */
#define TYPE_LIMITED_STRING (limited_string_get_type())

/* Cast instance */
#define LIMITED_STRING(obj) \
 (G_TYPE_CHECK_INSTANCE_CAST((obj), TYPE_LIMITED_STRING, LimitedString))

/* Cast class */
#define LIMITED_STRING_CLASS(klass) \
 (G_TYPE_CHECK_CLASS_CAST((klass), TYPE_LIMITED_STRING, LimitedStringClass))

/* Check instance */
#define IS_LIMITED_STRING(obj) \
 (G_TYPE_CHECK_INSTANCE_TYPE((obj), TYPE_LIMITED_STRING))

/* Check class */
#define IS_LIMITED_STRING_CLASS(klass) \
 (G_TYPE_CHECK_CLASS_TYPE((klass), TYPE_LIMITED_STRING))

/* Instance to class */
#define LIMITED_STRING_GET_CLASS(obj) \
 (G_TYPE_INSTANCE_GET_CLASS((obj), TYPE_LIMITED_STRING, LimitedStringClass))

/* ---------------------------------------------------------------- */

#include <stdio.h>

static void
limited_string_dispose (
  GObject * self ) {
    fprintf(stderr, "%s\n", __func__);
    G_OBJECT_CLASS(limited_string_parent_class)->dispose(self);
}

static void
limited_string_finalize (
  GObject * self ) {
    fprintf(stderr, "%s\n", __func__);
    G_OBJECT_CLASS(limited_string_parent_class)->finalize(self);
}

static void
limited_string_class_init (
  LimitedStringClass * pclass ) {
  GObjectClass * pobjectclass = (GObjectClass *) pclass;
    fprintf(stderr, "%s\n", __func__);
    pobjectclass->dispose = limited_string_dispose;
    pobjectclass->finalize = limited_string_finalize;
}

static void
limited_string_init (
  LimitedString * self ) {
    fprintf(stderr, "%s\n", __func__);
}

/* ---------------------------------------------------------------- */

int
main (
  int argc,
  char * * argv ) {
  LimitedString * pstring0 = NULL;
  LimitedString * pstring1 = NULL;
    fprintf(stderr, "d0: %s\n", __func__);
    g_type_init();
    fprintf(stderr, "d1: %s\n", __func__);
    pstring0 = g_object_new(
     TYPE_LIMITED_STRING, /* GObject type identifier */
     NULL ); /* sentinel */
    fprintf(stderr, "d2: %s\n", __func__);
    pstring1 = g_object_new(
     TYPE_LIMITED_STRING, /* GObject type identifier */
     NULL ); /* sentinel */
    fprintf(stderr, "d3: %s\n", __func__);
    if (pstring0) { g_object_unref(pstring0); }
    fprintf(stderr, "d4: %s\n", __func__);
    if (pstring1) { g_object_unref(pstring1); }
    fprintf(stderr, "d5: %s\n", __func__);
    return (0);
}
