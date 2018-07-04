/*
 * #+DESCRIPTION:       백준 10972, 다음 순열 문제를 푼 코드
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

bool next_permutation(vector<int> &a, int n) {
  int i = n-1;
  while(i > 0 && a[i-1] >= a[i]) {
    i -= 1;
  }

  if(i <= 0) return false;

  int j = n-1;
  while(a[j] <= a[i-1])
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
  vector<int > a(n);

  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  if(next_permutation(a, n)) {
    for(int i=0; i<n; i++) {
      cout << a[i] << ' ';
    }
  }
  else
    cout << "-1";

  cout << '\n';

  return 0;
}
