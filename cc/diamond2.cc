#include <iostream>
using namespace std;

class Base {
public:
  Base() {}
  virtual ~Base() {}
  virtual void foo() { cout << "Base::foo()" << endl; }
};

// virtual public: DerrivedA::foo() に決まって OK
// public: DerrivedA::foo() と、B 経由の Base::foo() で ambiguous
class DerrivedA : virtual public Base {
public:
  DerrivedA() {}
  virtual ~DerrivedA() {}
  virtual void foo() { cout << "DerrivedA::foo()" << endl; }
};

class DerrivedB : virtual public Base {
public:
  DerrivedB() {}
  virtual ~DerrivedB() {}
  // これ、ambiguous でエラー
  //virtual void foo() { cout << "DerrivedB::foo()" << endl; }
};

class MultiDerrived : public DerrivedA, public DerrivedB {
public:
  MultiDerrived() {}
  virtual ~MultiDerrived() {}
};

int main() {
  MultiDerrived md;
  md.foo(); // Base::foo ? DerrivedA::foo ? 
}