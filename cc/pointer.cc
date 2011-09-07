#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

class Hoge {
public:
    int fuga();
    int hoga();
    static int foo();
};

int Hoge::fuga() {
    return (printf("fuga fuga\n"));
}

int Hoge::hoga() {
    return (printf("hoga hoga\n"));
}

int Hoge::foo() {
    return (printf("foo foo\n"));
}

#define BufSize 100

int
main (
  int argc,
  char * * argv ) {
  Hoge * phoge = new Hoge();
  char * psz;
  FILE * pfile;
  int (* pfunc)() = Hoge::foo;
  int (Hoge::* pfunc2)() = &Hoge::hoga;
    phoge->hoga();
    phoge->fuga();
    printf("d0: %lp %lp %lp %lp %lp\n", phoge, &Hoge::hoga, &Hoge::fuga, &Hoge::hoga, Hoge::foo);
    printf("d1: %d %d %d %d\n", sizeof (phoge), sizeof (&Hoge::hoga), sizeof (&Hoge::fuga), sizeof (pfunc2));
    pfunc();
    psz = new char[100];
    snprintf(psz, BufSize, "/proc/%d/maps", getpid());
    pfile = fopen(psz, "r");
    while (fgets(psz, BufSize, pfile)) {
        printf(psz);
    }
    fclose(pfile);
    delete[] psz;

    return (0);
}



