/*
 * #+DESCRIPTION:  백준 1076, 저항 문제를 푼 코드
 * #+CATEGORY:
 * #+LEVEL:        -
 * #+FROM:         -
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(int argc, char **argv) {
  map<string, int> d = {
    {"black", 0}, {"brown", 1}, {"red", 2},
    {"orange", 3}, {"yellow", 4}, {"green", 5},
    {"blue", 6}, {"violet", 7}, {"grey", 8},
    {"white", 9}
  };

  string a,b,c;
  cin >> a >> b >> c;

  // ed: yellow violet red 입력을 처리하는 코드
  long long ans = (long long)(d[a]*10 + d[b]);
  for (int k=0; k<d[c]; k++) {
    ans *= 10LL;
  }

  cout << ans << '\n';
  return 0;
}
