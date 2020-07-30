/*
 * #+DESCRIPTION:  백준 1001번, A-B 문제를 푼 코드
 * #+CATEGORY:
 * #+LEVEL:        -
 * #+FROM:         -
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>

using namespace std;

int main(){
  int a,b;
  cin >> a >> b;

  if (a < 1 || a > 9)
    return 0;
  if (b < 1 || b > 9)
    return 0;

  cout << a - b;

  return 0;
}
