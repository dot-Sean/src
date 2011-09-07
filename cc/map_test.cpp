#include <iostream>
#include <map>
#include <string>

using namespace std;

int
main (
  int argc,
  char * * argv ) {
  map<string, const char *> map0;
  const char * aapsz[][2] = {
      { "abc", "ABC" },
      { "def", "DEF" },
      { "uvw", "UVW" },
      { "xyz", "XYZ" },
      { NULL, NULL },
  };
  int i;
  //int n = (sizeof (aapsz)) / (sizeof (const char * [2]));
    for (i = 0; aapsz[i][0]; i ++) {
        map0.insert(make_pair(string(aapsz[i][0]), aapsz[i][1]));
    }
  map<string, const char *>::iterator itrmap;
  string strKey("uvw");
    itrmap = map0.find(strKey);
    if (itrmap != map0.end()) {
        cout << "Found: " << strKey << " -> " << itrmap->second << endl;
    }
  map<string, const char *>::iterator itrmapEnd = map0.end();
    for (itrmap = map0.begin(); itrmap != itrmapEnd; itrmap ++) {
        cout << itrmap->first << ": " << itrmap->second << endl;
    }
    return (0);
}
