/*
 * #+DESCRIPTION:  백준 1074, Z 문제를 푼 코드
 * #+CATEGORY:     Divide & Conquer
 * #+LEVEL:        -
 * #+FROM:         중급1 분할정복 part 2
 * #+DATE:         2018-06-23-토
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
using namespace std;

int power2(int k) {
  return (1 << k);
}

int go (int n, int x, int y) {
  if(n == 1)
    return 2*x + y;  // ed: n==1인 경우 [2x2]칸이므로 x,y 값에 따라 0,1,2,3을 더해준다
  else {
    if(x < power2(n-1)) {
      if(y < power2(n-1))    // ed: 왼쪽 위
        return go(n-1, x, y);
      else                   // ed: 오른쪽 위
        return go(n-1, x, y-power2(n-1)) + power2(2*n-2);
    }
    else {
      if(y < power2(n-1))   // ed: 왼쪽 아래
        return go(n-1, x-power2(n-1), y) + power2(2*n-2)*2;
      else                  // ed: 오른쪽 아래
        return go(n-1, x-power2(n-1), y-power2(n-1)) + power2(2*n-2)*3;
    }
  }
}

int main() {
  int n,x,y;

  while(cin >> n >> x >> y) {
    cout << go(n,x,y) << '\n';
  }

  return 0;
}
