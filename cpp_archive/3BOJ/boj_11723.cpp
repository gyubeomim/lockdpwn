/*
 * #+DESCRIPTION:       백준 11723, 집합 문제를 푼 코드
 * #+CATEGORY:          BIT MASK
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              중급1 완전탐색0 비트마스크
 * #+DATE:              2018-06-25-월
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

char b[111];

int main() {
  int n = 20;
  int m;
  cin >> m;
  int s = 0;
  int x;

  while(m--) {
    scanf("%s", b);
    if(!strcmp(b, "add")) {
      scanf("%d", &x); x--;
      s = (s | (1 << x));
    }
    else if(!strcmp(b, "remove")) {
      scanf("%d", &x); x--;
      s = (s & ~(1 << x));
    }
    else if(!strcmp(b, "check")) {
      scanf("%d", &x); x--;
      int res = (s & (1 << s));
      if(res) puts("1");
      else puts("0");
    }
    else if(!strcmp(b, "toggle")) {
      scanf("%d", &x); x--;
      s = (s ^ (1 << x));
    }
    else if(!strcmp(b, "all")) {
      s = (1<<n) - 1;
    }
    else if(!strcmp(b, "empty")) {
      s = 0;
    }
  }
  return 0;
}
