/*
 * #+DESCRIPTION:       백준 9095, 1,2,3 더하기 문제를 푼 코드
 * #+CATEGORY:          RECURSIVE, EXAUSTIVE SEARCH
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              중급1 완전탐색1 재귀호출,비트마스크
 * #+DATE:              2018-07-07-토
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <iostream>
using namespace std;

int go (int count, int sum, int goal) {
  if(count > 10)
    return 0;
  if(sum > goal)
    return 0;
  if(sum == goal)
    return 1;

  int now = 0;
  for(int i=1; i<=3; i++) {
    now += go(count+1, sum+i, goal);
  }
  return now;
}

int main() {
  int t;
  cin >> t;

  while(t--) {
    int n;
    cin >> n;
    cout << go(0, 0, n) << '\n';
  }

  return 0;
}
