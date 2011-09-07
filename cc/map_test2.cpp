#include <iostream>
#include <map>
#include <string>

using namespace std;
typedef map<string, string> MapStrStr;
int
main (
  int argc,
  char * * argv ) {
  MapStrStr m;
  const char * aapsz[][2] = {
      { "abc", "ABC123" },
      { "def", "DEF123" },
      { "uvw", "UVW123" },
      { "xyz", "XYZ123" },
      { NULL, NULL },
  };
    for (int i = 0; aapsz[i][0]; i ++) {
        m[aapsz[i][0]] = aapsz[i][1];
    }
  MapStrStr::iterator i;
    if ((i = m.find(string("xyz"))) != m.end()) {
        cout << "Found: " << i->first << ": " << i->second << endl;
    }
    if ((i = m.find(string("xxx"))) != m.end()) {
        cout << "Found: " << i->first << ": " << i->second << endl;
    }
    for (i = m.begin(); i != m.end(); ++ i) {
        cout << i->first << ": " << i->second << endl;
    }
    return (0);
}
