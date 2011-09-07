#include <iostream>
#include <string>

#include "template.h"

template <typename T>
T
add (
  T a,
  T b ) {
    return (a + b);
}

// int add (int a, int b);
// float add (float a, float b);
// string add (string a, string b);

int
main (
  int argc,
  char * * argv ) {
  int n;
  float r;
  std::string s;
    n = add(1, 2);
    r = add(1.2, 3.4);
    s = add(std::string("Hello, "), std::string("World."));
    std::cout << n << std::endl;
    std::cout << r << std::endl;
    std::cout << s << std::endl;
    return (0);
}
