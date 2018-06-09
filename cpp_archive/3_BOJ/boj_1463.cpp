/*
 * +description:
 *  백준 1463, 1로 만들기 문제를 푼 정답 코드
 *             DP를 사용해서 문제를 풀었다
 *
 *  code from [boj 알고리즘기초, 다이나믹프로그래밍1 문제풀이1]
 *
 * +author: Edward Im (gyurse@gmail.com)
 */
#include <iostream>
using namespace std;

int d[10000001];

/*
   d[n] = min(d[n%3]+1, d[n%2]+1, d[n-1]+1)
 */
int go(int n) {
  if(n == 1) return 0;
  if(d[n] > 0) return d[n];

  d[n] = go(n-1) + 1;
  if(n%2 == 0) {
    int temp = go(n/2) + 1;
    if(d[n] > temp)
      d[n] = temp;
  }

  if(n%3 == 0) {
    int temp = go(n/3) + 1;
    if(d[n] > temp)
      d[n] = temp;
  }
  return d[n];
}

int main() {
  int n;
  cin >> n;
  cout << go(n) << endl;

  return 0;
}
