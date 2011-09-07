#include <xercesc/util/PlatformUtils.hpp>

#include <iostream.h>

int
main (
  int argc,
  char * * argv ) {
    try {
        XMLPlatformUtils::Initialize();
    } catch (const XMLException & e) {
        cerr << "Error during initialization! Message:\n" <<
         e.getMessage() << endl;
        XMLPlatformUtils::Terminate();
        return (1);
    }
    return (0);
}
