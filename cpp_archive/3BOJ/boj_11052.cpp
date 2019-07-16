/*
 * #+DESCRIPTION:  백준 11052, 붕어빵 판매하기 문제를 푼 정답코드
 * #+CATEGORY:     DP
 * #+LEVEL:        -
 * #+FROM:         boj 알고리즘기초 다이나믹프로그래밍1 문제풀이1
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }

  // d[i] = d[i-j] + a[j]
  vector<int> d(n+1);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=i; j++) {
      d[i] = max(d[i], d[i-j]+a[j]);
    }
  }
  cout << d[n] << endl;

  return 0;
}
