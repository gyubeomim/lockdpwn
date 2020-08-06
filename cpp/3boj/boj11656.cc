// @date:              2020.08.06.Thu
// @level:             1
// @category:          Basic
// @description:       접미사 배열
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  string S;
  cin >> S;

  vector<string> strs;
  for(int i=0; i<S.size(); i++) {
    string str;
    str = S.substr(i);
    strs.push_back(str);
  }

  sort(strs.begin(), strs.end(), [](const string &a,
                                    const string &b) {
                                   return a < b;
                                 });

  for(int i=0; i<strs.size(); i++) {
    cout <<strs[i] << endl;
  }

  return 0;
}
