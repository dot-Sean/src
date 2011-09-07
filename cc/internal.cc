#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class Hoge {
public:
    int n;
    virtual void func() {
        cout << "Hoge";
    }
};

class Fuga : public Hoge {
public:
    void func() {
        cout << "Fuga";
    }
};

int
main (
  int argc,
  char * * argv ) {
  Hoge * phoge;
    phoge = new Fuga();
    phoge->func();
    //phoge = new Fuga[10];
    //phoge->n = 256;
    //cout << phoge->n;
    //phoge[0]->func();
    return (0);
}
