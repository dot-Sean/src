#include <stdio.h>

static void foo () __attribute__ ((constructor)); // __CTOR_LIST__
static void bar () __attribute__ ((destructor)); // __DTOR_LIST__
static void hoge () __attribute__ ((section ("fuga"))); // in arbitrary section

static void hogehoge (int argc, char * * argv, char * * envp);

static void * __libc_subinit_hogehoge __attribute__ ((section ("__libc_subinit"))) = & (hogehoge); // invalid?

static void
hogehoge (
  int argc,
  char * * argv,
  char * * envp ) {
    printf("Fuga Fuga!\n");
}

static void
foo () {
    printf("Foo!\n");
}

static void
bar () {
    printf("Bar!\n");
}

static void
hoge () {
    printf("Hoge!\n");
}

int main (int argc, char * * argv) {
    printf("Hello World!\n");
    hoge();
    return (0);
}
