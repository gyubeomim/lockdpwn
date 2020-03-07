/*
 * #+DESCRIPTION:  백준 11652, 카드 문제를 푼 정답코드, sort 함수를 사용해 풀었다
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

typedef long long ll;
ll a[1000000];

int main() {
  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  sort(a, a+n);
  ll ans = a[0];
  int ans_cnt = 1;
  int cnt = 1;

  for(int i=1; i<n; i++) {
    if(a[i] == a[i-1])
      cnt += 1;
    else
      cnt = 1;

    if(ans_cnt < cnt ) {
      ans_cnt = cnt;
      ans = a[i];
    }
  }
  cout << ans << '\n';
  return 0;
}
