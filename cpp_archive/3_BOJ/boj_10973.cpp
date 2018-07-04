/*
 * #+DESCRIPTION:       백준 10973, 이전 순열 문제를 푼 코드
 * #+CATEGORY:          PERMUTATION
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              중급1 완전탐색0 순열
 * #+DATE:              2018-06-25-월
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;


bool prev_permutation(int *a, int n) {
  int i = n-1;

  while(i>0 && a[i-1] <= a[i])
    i -= 1;

  if(i <= 0) return false;

  int j = n-1;
  while(a[j] >= a[i-1])
    j -= 1;

  swap(a[i-1], a[j]);
  j = n-1;

  while(i < j) {
    swap(a[i], a[j]);
    i += 1;
    j -= 1;
  }
  return true;
}

int main() {
  int n;
  cin >> n;

  int a[10000];
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  if(prev_permutation(a,n)) {
    for(int i=0; i<n; i++) {
      cout << a[i] << ' ';
    }
  }
  else
    cout << "-1";

  cout << '\n';

  return 0;
}
