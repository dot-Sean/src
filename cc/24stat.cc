#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>

using namespace std;

int
main (
  int argc,
  char * * argv ) {
  char buf[1024];
  std::ifstream stats("/proc/stat");
    stats >> buf;
    while (strncmp(buf, "page", 9) != 0) {
        cout << "d:" << buf << "\n";
        stats >> buf;
    }
    return (0);
}
