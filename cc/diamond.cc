#include <iostream>
using namespace std;

class Base {
public:
  Base(): id(5) { cout << "Base()" << endl; }
  Base(int n): id(n) { cout << "Base(" << n << ")" << endl; }
  virtual ~Base() {}
  int GetBaseId() { return id; }
private:
  int id;
};

class DerrivedA : virtual public Base {
public:
  DerrivedA(int n) : Base(n) { cout << "DerivedA(" << n << ")" << endl; }
  virtual ~DerrivedA() {}
};

class DerrivedB : virtual public Base {
public:
  DerrivedB() { cout << "DerivedB()" << endl; }
  virtual ~DerrivedB() {}
};

class DerrivedC : virtual public DerrivedB {
public:
  DerrivedC() { cout << "DerivedC()" << endl; }
  virtual ~DerrivedC() {}
  int GetId() { return GetBaseId(); }
};

class MultiDerrived : public DerrivedA, virtual public DerrivedC {
public:
  MultiDerrived(int n) : DerrivedA(n) { cout << "MultiDerived(" << n << ")" << endl; }
  virtual ~MultiDerrived() {}
};

int main() {
  MultiDerrived md(10); // id を10の初期化のはずが・・・
  cout << md.GetId() << endl; // あれ？
}
