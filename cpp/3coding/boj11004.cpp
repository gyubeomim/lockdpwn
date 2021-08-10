/*
 * #+DESCRIPTION:  백준 11004, K번째 수 문제를 푼 정답코드, nth_element() 함수를 사용해서 문제를 풀었다
 * #+CATEGORY:     sort
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 정렬
 * #+DATE:         2018-06-19-화
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int a[5000000];

int main() {
  int n,k;
  cin >> n >> k;
  k -= 1;

  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  // ed: (a, a+n) 구간에서 a+k 범위만큼만 정렬한다
  nth_element(a, a+k, a+n);
  cout << a[k] << '\n';
  return 0;
}
