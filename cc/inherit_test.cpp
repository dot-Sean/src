#include <iostream>

enum {
    InitVal = 200, // const value in header file
};

class Base {
private:
    int nBase;
    bool fBase;
protected:
    Base(int arg1, int arg2 = InitVal);
    // copy constructor
    // pure virtual, so it's proteted and called only by parents
    Base(const Base & baseOther);
    // assignation operator
    Base & operator=(const Base & baseOther);
public:
    virtual ~Base();
    virtual int hoge() = 0;
};

namespace inherit_test {

class Derived : public Base {
private:
    int nDerived;
    friend std::ostream & operator<<(std::ostream & ostream, const Derived & derived);
public:
    // constructor
    Derived(int arg3);
    // copy constructor
    Derived(const Derived & derivedOther);
    Derived & operator=(const Derived & derivedOther);
    virtual ~Derived();
    int hoge();
};

};

// -------------------------------------------------------------------

// as if static variable in C lang
namespace {
    const int nStatic = 100;
};

#include <iomanip>

const int Width = 5;
Base::Base (
  int arg1,
  int arg2 ) :
  nBase(arg1),
  fBase(true) {
    // google with "Applicable Manipulators stream"
    std::cout.sync_with_stdio(true);
    std::cout << "Base constructor: " <<
     std::setw(Width) << std::setfill('.') << std::left << arg1 << ' ' <<
     std::setw(Width * 2) << std::hex << arg2 << ' ' << 
     std::setw(Width) << std::right << 511 << ' ' <<
     std::endl;
}

Base::Base (
  const Base & baseOther ) {
    this->nBase = baseOther.nBase;
    std::cout << "Base copy constructor" << std::endl;
}

Base &
Base::operator= (
  const Base & baseOther ) {
    std::cout << "Base assignation" << std::endl;
    this->nBase = baseOther.nBase;
    return (* this);
}

Base::~Base () {
    std::cout << "Base destructor" << std::endl;
}

// -------------------------------------------------------------------

using namespace inherit_test;

Derived::Derived (
  int arg3 ) :
  Base(arg3, 2047), // initialization list
  nDerived(arg3) {
    std::cout << "Derived constructor" << std::endl;
}

Derived::Derived (
  const Derived & derivedOther ) :
  Base(derivedOther),
  nDerived(derivedOther.nDerived) {
    std::cout << "Derived copy constructor" << std::endl;
}

Derived &
Derived::operator= (
  const Derived & derivedOther ) {
    Base::operator=(derivedOther);
    std::cout << "Derived assignation" << std::endl;
    this->nDerived = derivedOther.nDerived;
    return (* this);
}

Derived::~Derived () {
    std::cout << "Derived destructor" << std::endl;
}

int Derived::hoge () {
    return (8191);
}

std::ostream &
inherit_test::operator<< (
  std::ostream & ostream,
  const Derived & derived ) {
    ostream << "output: " << derived.nDerived;
    return (ostream);
}

// -------------------------------------------------------------------

int
main (
  int argc,
  char * * argv ) {
#if 1
  Base * pbase;
    pbase = new Derived(255);
  Derived derived0(0);
  Derived derived1 = derived0;
    derived0 = derived1;
    delete pbase;
#endif
  // Array members cannot be initialized.
  //Derived[] pderived = new Derived[] {{1,2}, {3,4}, {5,6}};
  //  delete pderived[];
    return (0);
}

