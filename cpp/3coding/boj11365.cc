// @level:             1
// @category:          String
// @description:       !밀비 급일
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  while(true) {
    string S;
    getline(cin, S);

    if(S == "END") {
      break;
    }
    reverse(S.begin(), S.end());

    cout << S << endl;
  }

  return 0;
}
