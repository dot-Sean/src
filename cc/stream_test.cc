#include <iostream>
#include <fstream>
#include <strstream>

int
main (
  int argc,
  char * * argv ) {
  std::ifstream input("/etc/fstab");
  //std::strstream buf;
  char buf[1024];
    while (! input.eof()) {
        input >> buf;
        std::cout << buf << std::endl;
        //std::cout << buf.str();
        //buf.seekp(0);
    }
    return (0);
}
