/*
 * #+DESCRIPTION:       백준 2022, 사다리 문제를 푼 코드
 * #+CATEGORY:          Binary Search
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              중급1 이분탐색으로 정답찾기 part 2
 * #+DATE:              2018-06-25-월
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
  double x,y,c;

  while(scanf("%lf %lf %lf", &x, &y, &c)==3) {
    double left = 0;
    double right = min(x,y);

    while(abs(right-left) > 1e-6) {    // ed: 실수는 이와같이 while문을 작성한다
      double mid = (left+right) / 2.0;
      double d = mid;
      double h1 = sqrt(x*x - d*d);
      double h2 = sqrt(y*y - d*d);
      double h = (h1*h2) / (h1+h2);    // ed: 수식을 이용해 h를 구하고

      if(h > c)     // ed: c보다 큰지 작은지에 따라 이분탐색을 실시한다
        left = mid;
      else
        right = mid;
    }
    printf("%.3lf\n", left);
  }
  return 0;
}
