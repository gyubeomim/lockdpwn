#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int t,n;
  vector<string> vs;
  cin >> t;

  while(t--) {
    cin >> n;
    vs = vector<string>(n);

    for(int i=0; i<n; i++) {
      cin >> vs[i];
    }

    sort(vs.begin(), vs.end());
    bool result = true;

    for(int i=1; i<n; i++) {
      string& a = vs[i-1];
      string& b = vs[i];

      if(a.size() > b.size()) continue;
      if(a == b.substr(0, a.size())) {
        result = false;
        break;
      }
    }
    puts(result ? "YES":"NO");
  }
  return 0;
}
