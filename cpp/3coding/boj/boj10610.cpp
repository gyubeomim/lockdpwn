/*
 * #+DESCRIPTION:  백준 10610, 30 문제를 푼 코드
 * #+CATEGORY:     GREEDY
 * #+LEVEL:        -
 * #+FROM:         중급1 그리디 알고리즘 part 2
 * #+DATE:         2018-06-21-목
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
  string s;
  cin >> s;

  int sum=0;
  for(char c : s) {
    sum += c - '0';
  }

  sort(s.begin(), s.end());

  // ed: 끝자리 수가 0으로 끝나고 각 자리수의 합이 3의 배수이면 2,3,5의 공통배수이므로 30의 배수가 된다
  if(s[0] == '0' && sum%3 == 0) {
    reverse(s.begin(), s.end());
    cout << s << '\n';
  }
  else
    cout << "-1" << '\n';

  return 0;
}
