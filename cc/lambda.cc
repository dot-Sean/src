#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>
using namespace std;

struct hoge {
  int n;
};

void foo (struct hoge a) {}

int main (
  int argc,
  char * * argv ) {
  using namespace boost::lambda;
  vector<int> vec;
  vec.push_back(10);
  vec.push_back(23);
  vec.push_back(45);
  vec.push_back(76);
  vec.push_back(98);
  // 5で割り切れて30より大きい要素を探す。
  vector<int>::iterator it =
   find_if(vec.begin(), vec.end(), 0 == _1 % 5 && _1 > 30);
  cout << "found:" << *it << endl;
  // それぞれの要素について、
  // 2で割り切れるかそうでないかによってメッセージを表示。
  std::for_each(vec.begin(), vec.end(),
    if_(_1 % 2 == 0) [
      cout << _1 << "は偶数\n"
    ].else_[
      cout << _1 << "は奇数\n"
    ]
  );
  // /usr/include/boost/lambda/if.hpp
  //typeid (_1);
  foo(hoge());
  return (0);
}
