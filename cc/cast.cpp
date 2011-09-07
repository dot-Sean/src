#include <iostream>

using namespace std;

void
foo (char * psz) {
    cout << "Hello: " << psz << endl;
}

int
main (
  int argc,
  char * * argv ) {
  const char * psz = "World";
    foo(const_cast<char *>(psz));
    return (0);
}
