/*
 * #+DESCRIPTION:  백준 2745, 진법변환 문제를 푼 정답 코드
 * #+CATEGORY:     수학 진법
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 수학1
 * #+DATE:         2018-06-12-화
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
  int ans = 0;
  string s;
  int b;
  cin >> s >> b;

  for(int i=0; i<s.size(); i++) {
    if('0' <= s[i] && s[i] <= '9')
      ans = ans*b + (s[i] - '0');
    else
      ans = ans*b + (s[i] - 'A' + 10);
  }
  cout << ans << endl;

  return 0;
}
