#include <iostream>
#include <list>
#include <numeric>
using namespace std;
int
main (
  int argc,
  char * * argv ) {
  int an[] = { 1, 2, 3, 4, 5 };
  list<int> ln(& an[0], & an[5]);
  list<int>::iterator it;
  list<int>::iterator begin = ln.begin();
  list<int>::iterator end = ln.end();
    for (it = begin; it != end; ++ it) {
        cout << (* it) << endl;
    }
  //int n = accumulate(begin, end, 0);
  int n = accumulate(ln.rbegin(), ln.rend(), 0);
    cout << "d: " << n << endl;
    return (0);
}
