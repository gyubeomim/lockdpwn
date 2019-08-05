/*
 * #+DESCRIPTION:       백준 2805, 나무 자르기 문제를 푼 코드
 * #+CATEGORY:          Binary Search
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              중급1 이분탐색으로 정답찾기 part 1
 * #+DATE:              2018-06-24-일
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

bool check(vector<ll> &a, ll mid, ll m) {
  int n = a.size();
  ll cnt = 0;
  for(int i=0; i<n; i++) {
    if(a[i]-mid > 0)
      cnt += a[i]-mid;
  }
  return cnt >= m;
}

int main() {
  int n;
  ll m;
  cin >> n >> m;

  vector<ll> a(n);
  ll l=0;
  ll r=0;

  for(int i=0; i<n; i++) {
    cin >> a[i];
    if(r < a[i]) r = a[i];
  }

  ll ans = 0;
  while(l <= r) {
    ll mid = (l+r)/2;
    if(check(a,mid,m)) {
      ans = max(ans,mid);
      l = mid+1;
    }
    else
      r = mid-1;
  }
  cout << ans << '\n';
  return 0;
}
