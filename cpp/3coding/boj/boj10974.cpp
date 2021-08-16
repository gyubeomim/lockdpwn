/*
 * #+DESCRIPTION:       백준 10974, 모든 순열 문제를 푼 코드
 * #+CATEGORY:          PERMUTATION
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              중급1 순열
 * #+DATE:              2018-06-25-월
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<int> a(n);
  for(int i=0; i<n; i++) {
    a[i] = i+1;
  }

  // ed: next_permutation 함수를 사용할 떄는 do while() 문법을 사용한다
  do {
    for(int i=0; i<n; i++) {
      cout << a[i] << ' ';
    }
    cout << '\n';
  } while (next_permutation(a.begin(), a.end()));

  return 0;
}
