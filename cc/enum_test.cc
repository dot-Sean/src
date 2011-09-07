#include <stdio.h>

// Does not compile
enum Foo { hoge, fuga };
//enum Bar { hoge, fuga };

int
main (
  int argc,
  char * * argv ) {
  Foo foo = hoge;
  //Bar bar = hoge;
    return (0);
}