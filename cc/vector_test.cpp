// http://www5c.biglobe.ne.jp/~ecb/cpp/

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <set>

using namespace std;

class Hoge {
protected:
    string s;
public:
    static int n;
    Hoge () {
        std::cerr << "created (no arg)" << std::endl;
        this->s = "no arg";
    }
    Hoge (const string & s) {
        this->s = s;
        std::cerr << "created: " << this->s << std::endl;
    }
    // Copy constructor
    Hoge (const Hoge & hoge) {
        this->s = "copy: " + hoge.s;
        std::cerr << "created (copy): " << this->s << std::endl;
    }
    virtual ~Hoge () {
        ++ this->n;
        std::cerr << "deleted: " << this->s << std::endl;
    }
    const string & get () {
        return (this->s);
    }
    const char * get_c_str () {
        return (this->s.c_str());
    }
    int operator< (const Hoge & hoge) const {
        return (1);
    }
};

int Hoge::n = 0;

typedef list<string> StrList;
typedef vector<int> IntVector;
typedef set<Hoge> HogeSet;
typedef vector<Hoge> HogeVec;

int
main (
  int argc,
  char * * argv ) {
  const char * apsz[] = { "abc", "123", "xyz", "789", NULL };
  StrList strlist;
  const char * * ppsz;
  string hoge = "HOGE";
    for (ppsz = apsz; (* ppsz); ppsz ++) {
        cout << (* ppsz) << " " << flush;
        strlist.push_front(string(* ppsz));
    }
    cout << endl;
  StrList::iterator itrstrlist;
  StrList::iterator itrstrlistBegin;
  StrList::iterator itrstrlistEnd;
    itrstrlistEnd = strlist.end();
    for (itrstrlist = strlist.begin(); itrstrlist != itrstrlistEnd;
     itrstrlist ++ ) {
        cout << (* itrstrlist) << endl;
    }
    cout << endl;
  StrList::reverse_iterator ritrstrlist;
  StrList::reverse_iterator ritrstrlistBegin;
  StrList::reverse_iterator ritrstrlistEnd;
    ritrstrlistEnd = strlist.rend();
    for (ritrstrlist = strlist.rbegin(); ritrstrlist != ritrstrlistEnd;
     ritrstrlist ++ ) {
        cout << (* ritrstrlist) << endl;
    }
    cout << endl;
  IntVector intvec;
  int i;
    for (i = 1; i <= 10; i ++) {
        intvec.push_back(i * 10);
    }
  int n = intvec.size();
    for (i = 0; i < n; i ++) {
        cout << intvec.at(i) << endl;
        intvec.at(i) *= 2;
    }
    cout << endl;
  IntVector::iterator itrintvec;
  IntVector::iterator itrintvecEnd;
    random_shuffle(intvec.begin(), intvec.end());
    itrintvecEnd = intvec.end();
    for (itrintvec = intvec.begin(); itrintvec != itrintvecEnd;
     itrintvec ++ ) {
        cout << (* itrintvec) << endl;
    }
    cout << endl;
    sort(intvec.begin(), intvec.end());
    for (itrintvec = intvec.begin(); itrintvec != itrintvecEnd;
     itrintvec ++ ) {
        cout << (* itrintvec) << endl;
    }
    cout << endl;
    // ---------------------------------------------------------------
    Hoge::n = 0;
  HogeSet hogeset;
    for (i = 0; i < 3; i ++) {
      ostringstream buf;
        buf << "Instance for set: " << i;
        hogeset.insert(Hoge(buf.str()));
    }
    cerr << "Number of instances created: " << Hoge::n << endl;
    cerr << "----" << endl;
    // ---------------------------------------------------------------
    Hoge::n = 0;
  HogeVec hogevec(3);
    for (i = 0; i < 3; i ++) {
      ostringstream buf;
        buf << "Instance for vector: " << i;
        hogevec.push_back(Hoge(buf.str()));
    }
    cerr << "Number of instances created: " << Hoge::n << endl;
    cerr << "----" << endl;
    // ---------------------------------------------------------------
    return (0);
}
