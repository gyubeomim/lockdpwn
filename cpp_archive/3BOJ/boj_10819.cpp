/*
 * #+DESCRIPTION:       백준 10819, 차이를 최대로 문제를 푼 코드
 * #+CATEGORY:          PERMUTATION, EXAUSTIVE SEARCH
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              중급1 완전탐색1 순열 사용하기
 * #+DATE:              2018-06-26-화
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int calculate(vector<int> &a) {
  int sum = 0;
  for(int i=1; i<a.size(); i++) {
    sum += abs(a[i]-a[i-1]);
  }
  return sum;
}

int main() {
  int n;

  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  sort(a.begin(), a.end());
  int ans = 0;

  // ed: next_permutation은 do while() 구문을 사용한다
  do {
    int temp = calculate(a);
    ans = max(ans, temp);
  } while (next_permutation(a.begin(), a.end()));

  cout << ans << '\n';

  return 0;
}
