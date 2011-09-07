#include "tclass.h"

#include <iostream>
using namespace std;

int
main (
  int argc,
  char * * argv ) {
  Hoge<int> hoge(300, 400);
    cout << hoge.get() << endl;
    return (0);
}

    