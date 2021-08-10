/*
 * #+DESCRIPTION:       백준 2110, 공유기 설치 문제를 푼 코드
 * #+CATEGORY:          Binary Search
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              http://meylady.tistory.com/13
 * #+DATE:              2018-06-24-일
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
ll arr[200005];
ll n,c;

ll binarysearch(ll l, ll r) {
  ll L = l;
  ll R = r;
  ll ans = 0;

  while(L <= R) {
    ll mid = (L+R) / 2;
    ll cc = 1;
    ll wifi = arr[0];

    for(int i=1; i<n; i++) {
      if(arr[i] - wifi >= mid) {
        cc++; // 공유기 설치
        wifi = arr[i];
      }
    }

    if(cc < c)
      R = mid-1;
    else {
      if(mid > ans)
        ans = mid;
      L = mid + 1;
    }
  }
  return ans;
}

int main(int argc, char **argv) {
  cin >> n  >> c;

  for(int i=0; i<n; i++)
    cin >> *(arr+i);

  sort(arr, arr+n);

  ll max = arr[n-1] - arr[0];
  ll ans = binarysearch(0, max);
  cout << ans << endl;

  return 0;
}
