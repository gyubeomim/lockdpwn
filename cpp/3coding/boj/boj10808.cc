// @level:             1
// @category:          Basic
// @description:       알파벳 개수
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  string S;
  cin >> S;

  map<char, int> words;
  for(int i=0; i<S.size(); i++) {
    words[S[i]] += 1;
  }

  for(char c='a'; c<='z'; c++) {
    cout << words[c] << ' ' ;
  }
  cout << endl;

  return 0;
}
