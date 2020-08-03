// @level:             1
// @category:          Basic
// @description:       문자열
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int T;
  cin >> T;

  while(T--) {
    string S;
    cin >> S;

    char top = S[0];
    char bottom = S[S.size()-1];

    cout << top << bottom << endl;
  }

  return 0;
}
