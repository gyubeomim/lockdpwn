/*
 * #+DESCRIPTION:       백준 2110, 공유기 설치 문제를 푼 코드
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

bool possible(vector<int> &a, int c, int x) {
  int cnt=1;
  int last = a[0];

  for(int house : a) {
    if(house - last >= x) {
      cnt += 1;
      last = house;
    }
  }
  return cnt >= c;
}

int main() {
  int n,c;
  cin >> n >> c;

  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  sort(a.begin(), a.end());

  int l = 1;
  int r = a[n-1] - a[0];
  int ans = l;

  while(l<=r) {
    int mid = (l+r)/2;
    if(possible(a,c,mid)) {
      if(ans < mid)
        ans = mid;
      l = mid+1;
    }
    else
      r = mid-1;
  }
  cout << ans << '\n';

  return 0;
}
