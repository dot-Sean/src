#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int
main (
  int argc,
  char * * argv ) {
  std::string str;
    while (cin >> str) {
        cout << str;
        cout << str.data();
    }
    return (0);
}
