/*
 * #+DESCRIPTION:  백준 1541, 잃어버린 괄호 문제를 푼 코드, 그리디 알고리즘을 사용해 풀었다
 * #+CATEGORY:     GREEDY
 * #+LEVEL:        -
 * #+FROM:         중급1 그리디 알고리즘 part 2
 * #+DATE:         2018-06-21-목
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
  string s;
  cin >> s;
  vector<int> num;
  vector<int> sign;

  bool minus = false;
  int cur=0;
  sign.push_back(1);

  for(int i=0; i<s.size(); i++) {
    if(s[i] == '+' || s[i] == '-') {
      if(s[i] == '+')
        sign.push_back(1);
      else
        sign.push_back(-1);

      num.push_back(cur);
      cur = 0;
    }
    else
      cur = cur*10 + (s[i]-'0');
  }
  num.push_back(cur);
  int ans=0;
  minus = false;

  for(int i=0; i<num.size(); i++) {
    // ed: (-) 부호가 나오면 뒤에 있는 숫자들은 전부 뺀다
    if(sign[i] == -1)
      minus = true;

    if(minus) ans -= num[i];
    else      ans += num[i];
  }
  cout << ans << '\n';

  return 0;
}
