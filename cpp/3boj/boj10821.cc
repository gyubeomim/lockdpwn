// @level:             1
// @category:          Basic
// @description:       10821. 정수의 개수
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  string str;
  cin >> str;

  int answer=1;
  for(int i=0; i<str.size(); i++) {
    if(str[i] == ',') {
      answer++;
    }
  }

  cout << answer << endl;

  return 0;
}
