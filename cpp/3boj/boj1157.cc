// @level:             1
// @category:          String
// @description:       단어 공부
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  map<char,int> word_count;

  string S;
  cin >> S;

  transform(S.begin(), S.end(), S.begin(), ::tolower);

  for(int i=0; i<S.size(); i++) {
    word_count[S[i]] += 1;
  }

  auto it = max_element(word_count.begin(), word_count.end(), [](const pair<char,int> &a,
                                                                 const pair<char,int> &b) {
                                                                return a.second < b.second;
                                                              });
  char argmax = it->first;
  int curr_max = it->second;

  bool is_duplicate = false;

  // check duplication.
  for(char c='a'; c<='z'; c++) {
    if(word_count[c] >= curr_max && c != argmax) {
      is_duplicate = true;
    }
  }

  if(is_duplicate) {
    cout << '?' << endl;
  }
  else {
    cout << (char)(argmax - 32) << endl;
  }

  return 0;
}
