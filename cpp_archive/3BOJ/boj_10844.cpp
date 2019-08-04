/*
 * #+DESCRIPTION:  백준 10844, 쉬운 계단수 문제를 푼 정답코드
 * #+CATEGORY:     DP
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 다이나믹프로그래밍1 문제풀이2
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
using namespace std;

long long d[101][10];
long long mod = 1000000000;

int main() {
  int n;
  cin >> n;

  // 한 자리수의 경우
  for(int i=1; i<=9; i++)
    d[1][i] = 1;

  // 두 자리수 이상 부터
  for(int i=2; i<=n; i++) {
    for(int j=0; j<=9; j++) {
      d[i][j] = 0;

      // d[i][j] = d[i-1][j-1] + d[i-1][j+1]
      if(j-1 >= 0) d[i][j] += d[i-1][j-1];
      if(j+1 <= 9) d[i][j] += d[i-1][j+1];

      d[i][j] %= mod;
    }
  }

  long long ans=0;
  for(int i=0; i<=9; i++) {
    ans += d[n][i];
  }
  ans %= mod;
  cout << ans << endl;

  return 0;
}
