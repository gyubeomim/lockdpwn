/*
 * #+DESCRIPTION:       백준 1476, 날짜 계산 문제를 푼 코드
 * #+CATEGORY:          BRUTE FORCE
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              중급1 완전탐색1 그냥다해보기
 * #+DATE:              2018-06-25-월
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
using namespace std;

int main() {
  int E,S,M;
  cin >> E >> S >> M;

  int e=1,s=1,m=1;

  for(int i=1;;i++) {
    if(e==E && s==S && m==M) {
      cout << i << '\n';
      break;
    }

    s++, e++, m++;

    if(s==29) s=1;
    if(e==16) e=1;
    if(m==20) m=1;
  }

  return 0;
}
