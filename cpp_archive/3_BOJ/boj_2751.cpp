/*
 * #+DESCRIPTION:  백준 2751, 수 정렬하기2 문제를 푼 정답코드
 * #+CATEGORY:     sort
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 정렬
 * #+DATE:         2018-06-18-월
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int a[1000001];

int main() {
  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    scanf("%d\n", &a[i]);
  }

  sort(a, a+n);

  for(int i=0; i<n; i++)
    printf("%d\n", a[i]);

  return 0;
}
