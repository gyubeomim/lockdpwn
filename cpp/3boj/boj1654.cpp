/*
 * #+DESCRIPTION:       백준 1654, 랜선 자르기 문제를 푼 코드
 * #+CATEGORY:          Binary Search
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              중급1 이분탐색으로 정답찾기 part 1
 * #+DATE:              2018-06-24-일
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
using namespace std;

long long a[10000];
int n,m;

bool check(long long x) {
  int cnt = 0;
  for(int i=0; i<n; i++) {
    cnt += a[i] / x;

  return cnt >= m;
}

int main() {
  scanf("%d %d", &n, &m);
  long long max = 0;

  for(int i=0; i<n; i++) {
    cin >> a[i];
    if(max < a[i])
      max = a[i];
  }

  long long ans = 0;
  long long left = 1;
  long long right = max;

  while(left <= right) {
    long long mid = (left+right)/2;

    if(check(mid)) {
      if(ans < mid)
        ans = mid;
      left = mid+1;
    }
    else
      right = mid-1;
  }
  cout << ans << '\n';
  return 0;
}
