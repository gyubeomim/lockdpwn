// @date:              2020.08.01.Sat
// @level:             1
// @category:          Basic
// @description:       10987. 모음의 개수
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  string S;
  cin >> S;

  int answer=0;
  for(int i=0; i<S.size(); i++) {
    if(S[i] == 'a' ||
       S[i] == 'e' ||
       S[i] == 'i' ||
       S[i] == 'o' ||
       S[i] == 'u') {
      answer++;
    }
  }

  cout << answer << endl;

  return 0;
}
