// @date:              2020.08.01.Sat
// @level:             1
// @category:          Basic
// @description:       2744. 대소문자 바꾸기
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  string str;
  cin >> str;

  for(int i=0; i<str.size(); i++) {
    if(str[i] >= 'a' && str[i] <= 'z') {
      str[i] -= 32;
    }
    else if (str[i] >= 'A' && str[i] <= 'Z') {
      str[i] += 32;
    }
  }

  cout << str << endl;

  return 0;
}
