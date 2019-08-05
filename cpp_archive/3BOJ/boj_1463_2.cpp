/*
 * #+DESCRIPTION:       백준 1463, 1로 만들기 문제를 푼 코드
 * #+CATEGORY:          DP
 * #+TIME_COMPLEXITY:   O(N)
 * #+LEVEL:             -
 * #+FROM:              알고리즘기초1 다이나믹프로그래밍1 문제풀이1
 * #+DATE:              2018-07-14-토
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <iostream>
using namespace std;

int d[1000001];

// ed: Bottom Up 방식으로 문제를 푼 경우
int go (int n) {
  d[1] = 0;
  for(int i=2; i<=n; i++) {
    d[i] = d[i-1] + 1;
    if(i%2==0 && d[i] > d[i/2]+1) {
      d[i] = d[i/2] + 1;
    }
    if(i%3==0 && d[i] > d[i/3]+1) {
      d[i] = d[i/3] + 1;
    }
  }
}

int main() {
  int n;
  cin >> n;

  go(n);
  cout << d[n] << '\n';

  return 0;
}
