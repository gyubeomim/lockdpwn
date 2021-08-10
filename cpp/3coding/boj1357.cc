// @date:              2020.08.01.Sat
// @level:             1
// @category:          Math
// @description:       1357. 뒤집힌 덧셈
#include <bits/stdc++.h>

using namespace std;

int Rev(string s) {
  reverse(s.begin(), s.end());

  while(s[0] == '0') {
    s.erase(s.begin());
  }

  return stoi(s);
}

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int X,Y;
  cin >> X>>Y;

  int answer = Rev(to_string(Rev(to_string(X)) + Rev(to_string(Y))));
  cout << answer << endl;

  return 0;
}
