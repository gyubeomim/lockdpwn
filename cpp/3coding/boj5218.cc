// @level:             1
// @category:          Basic
// @description:       알파벳 거리
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int T;
  cin >> T;

  while(T--) {
    string A,B;
    cin >> A >> B;

    cout << "Distances: ";
    for(int i=0; i<A.size(); i++) {
      int dist=0;
      if(A[i] > B[i]) {
        dist = B[i] + 26 - A[i];
      }
      else {
        dist = B[i] - A[i];
      }
      cout << dist << ' ';
    }
    cout << endl;
  }

  return 0;
}
