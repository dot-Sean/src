#include <iostream>

class Base {
  int n;
public:
  Base();
  void foo();
  void bar();
  ~Base();
};

Base::Base () {
    std::cout << "d: constructor0" << std::endl;
}

void Base::foo() { std::cout << "d: foo" << std::endl; }
void Base::bar() { std::cout << "d: bar" << std::endl; }

Base::~Base () {
    std::cout << "d: destructor" << std::endl;
}

class VirtualBase {
  int n;
public:
  VirtualBase();
  virtual void foo();
  virtual void bar();
  virtual ~VirtualBase();
};

VirtualBase::VirtualBase () {
    std::cout << "d: constructor1" << std::endl;
}

void VirtualBase::foo() { std::cout << "d: virtual foo" << std::endl; }
void VirtualBase::bar() { std::cout << "d: virtual bar" << std::endl; }

VirtualBase::~VirtualBase () {
    std::cout << "d: virtual destructor" << std::endl;
}

class VirtualDerived: public VirtualBase {
  int m;
public:
  void hoge();
  virtual void buzz();
};

void VirtualDerived::hoge() { std::cout << "d: virtual hoge" << std::endl; }
void VirtualDerived::buzz() { std::cout << "d: virtual buzz" << std::endl; }

int
main (
  int argc,
  char * * argv ) {
  Base * pbase = new Base();
  VirtualBase * pvirtualbase = new VirtualBase();
    std::cout << sizeof (* pbase) << std::endl;
    std::cout << sizeof (* pvirtualbase) << std::endl;
    std::cout << "Calling non-virtual:" << std::endl;
    pbase->foo();
    pbase->bar();
    std::cout << "Calling virtual:" << std::endl;
    pvirtualbase->foo();
    pvirtualbase->bar();
    std::cout << "Done:" << std::endl;
    std::cout << "Calling virtual:" << std::endl;
  VirtualDerived * pvirtualderived = new VirtualDerived();
    pvirtualderived->foo();
    pvirtualderived->bar();
    pvirtualderived->buzz();
    std::cout << "Done:" << std::endl;
    delete pvirtualderived;
    delete pvirtualbase;
    delete pbase;
    return (0);
}
