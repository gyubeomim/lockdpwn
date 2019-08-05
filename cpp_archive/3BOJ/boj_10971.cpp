/*
 * #+DESCRIPTION:       백준 10971, 외판원 순회2 문제를 푼 코드
 * #+CATEGORY:          EXAUSTIVE SEARCH, PERMUTATION
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

int a[20][20];

int main() {
  int n;
  cin >> n;

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> a[i][j];
    }
  }

  vector<int> d(n);
  for(int i=0; i<n; i++)
    d[i] = i;

  int ans = 2147483647;

  do {
    bool ok = true;
    int sum = 0;

    // ed: 모든 경우의 수를 탐색하는 코드
    for(int i=0; i<n-1; i++) {
      if(a[d[i]][d[i+1]] == 0)
        ok = false;
      else
        sum += a[d[i]][d[i+1]];
    }

    // ed: 원래 도시로 돌아오는 코드
    if(ok && a[d[n-1]][d[0]] != 0) {
      sum += a[d[n-1]][d[0]];
      if(ans > sum)
        ans = sum;
    }
  } while (next_permutation(d.begin()+1, d.end()));

  cout << ans << '\n';

  return 0;
}
