#include <iostream>

using namespace std;

int
main (
  int argc,
  char * * argv ) {
    try {
        throw "Hoge!";
    } catch (const char * psz) {
        cout << "Exception: " << psz << endl;
    }
    return (0);
}
