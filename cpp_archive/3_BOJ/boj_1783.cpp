/*
 * #+DESCRIPTION:  백준 1773, 병든 나이트 문제릂 푼 코드, N,M 제한이 매우 크므로 수식을 사용해 풀었다
 * #+CATEGORY:     GREEDY
 * #+LEVEL:        -
 * #+FROM:         중급1 그리디 알고리즘 part 2
 * #+DATE:         2018-06-21-목
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
  int height, width;
  cin >> height >> width;

  if(height == 1)
    cout << 1;
  else if(height == 2)
    cout << min(4, (width+1)/2);
  else if(height >= 3) {
    if(width >= 7)
      cout << width - 2;
    else
      cout << min(4, width);
  }

  return 0;
}
