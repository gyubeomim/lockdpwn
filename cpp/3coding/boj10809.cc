// @date:              2020.07.31.Fri
// @level:             1
// @category:          Basic
// @description:       10809. 알파벳 찾기
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  string S;
  cin >> S;

  map<int, int> alphabet;
  for(int i=0; i<26; i++) {
    if(alphabet[i] == 0) {
      alphabet[i] = -1;
    }
  }

  for(int i=0; i<S.size(); i++) {
    if(alphabet[S[i]-'a'] == -1)
      alphabet[S[i]-'a'] = i;
  }


  for(int i=0; i<26; i++) {
    cout << alphabet[i] << ' ';
  }
 

  return 0;
}
