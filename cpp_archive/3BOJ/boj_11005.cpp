/*
 * #+DESCRIPTION:  백준 11005, 진법변환2 문제를 푼 정답코드
 * #+CATEGORY:     수학, 이진법
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
  int n,b;
  cin >> n >> b;
  string ans = "";

  while(n>0) {
    int r = n%b;

    if(r<10)
      ans += r + '0';
    else
      ans += (r-10+'A');

    n /= b;
  }
  reverse(ans.begin(), ans.end());
  cout << ans << endl;
  return 0;
}
