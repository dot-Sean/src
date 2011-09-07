#include <iostream>
#include <string.h>

class Hoge {
    char * psz;
public:
    char sz[256];
    Hoge (const char * psz) {
        this->psz = strdup(psz);
    }
    ~Hoge () {
        free(this->psz);
        std::cerr << "deleted" << std::endl;
    }
    const char * get () {
        return (this->psz);
    }
};

void
func (
  Hoge * phoge ) {
    std::cout << phoge->get() << std::endl;
}

int
main (
  int argc,
  char * * argv ) {
  int rc = 1;
  /* dynamic */
  FILE * pfile = NULL;
  Hoge * phoge;
//std::cout << (sizeof (((Hoge *) 0)->sz)) << std::endl;
std::cout << (sizeof (phoge->sz)) << std::endl;
    do {
        std::cout << "Hello" << std::endl;
      std::auto_ptr<Hoge> phoge0(new Hoge("World"));
      //std::auto_ptr<Hoge> phoge1(new Hoge("Bar"));
        std::cout << phoge0->get() << std::endl;
        if (0) {
            break;
        }
        std::cerr << "cp0" << std::endl;
        {
          std::auto_ptr<Hoge> phoge1(new Hoge("Bar"));
            func(phoge1.get());
        }
        std::cerr << "cp1" << std::endl;
        rc = 0;
    } while (0);
    if (pfile) { fclose(pfile); }
    return (rc);
}
