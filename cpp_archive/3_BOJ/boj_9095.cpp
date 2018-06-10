/*
 * +description:
 *  백준 9095, 1,2,3 더하기 문제를 푼 정답 코드
 *             DP를 사용해서 풀었다
 *
 *  code from [boj 알고리즘기초 다이나믹프로그래밍1 문제풀이1]
 *
 * +author: Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
using namespace std;

int d[11];

int main() {
  int T,n;
  cin >> T;

  d[0] = 1;
  d[1] = 1;
  d[2] = 2;
  d[3] = 4;

  while(T--) {
    cin >> n;

    // d[i] = d[i-1] + d[i-2] + d[i-3]
    for(int i=4; i<=n; i++) {
      d[i] = d[i-1] + d[i-2] + d[i-3];
    }
    cout << d[n] << endl;
  }

  return 0;
}
