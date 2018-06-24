/*
 * #+DESCRIPTION:  백준 11729, 하노이탑 이동순서 문제를 푼 코드
 * #+CATEGORY:     Divide & Conquer
 * #+LEVEL:        -
 * #+FROM:         중급1 분할정복 part 1
 * #+DATE:         2018-06-21-목
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
using namespace std;

// ed: n개의 탑을 x에서 y로 이동하는 함수
void solve(int n, int x, int y) {
  if(n == 0) return;

  solve(n-1, x, 6-x-y);
  cout << x << ' ' << y << '\n';
  solve(n-1, 6-x-y, y);
}

int main() {
  int n;
  cin >> n;

  cout << (1<<n)-1 << '\n';
  solve(n,1,3);

  return 0;
}
