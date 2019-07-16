/*
 * #+DESCRIPTION:  백준 2193, 이친수 문제를 푼 정답 코드
 * #+CATEGORY:     DP
 * #+LEVEL:        *
 * #+FROM:         알고리즘기초 다이나믹프로그래밍1 문제풀이2
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
using namespace std;

long long d[91];

int main() {
  int n;
  cin >> n;
  d[1] = 1;
  d[2] = 1;

  // d[i] = d[i-1] + d[i-2]
  for(int i=3; i<=n; i++) {
    d[i] = d[i-1] + d[i-2];
  }
  cout << d[n] << endl;
  return 0;
}
