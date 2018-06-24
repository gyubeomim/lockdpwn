#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

ll arr[200005];
ll n,c;

ll binarysearch(ll l, ll r) {
  ll ans = 0;

  while(l <= r) {
    ll mid = (l+r)/2;
    ll cc = 1;
    ll wifi = arr[0];

    for(int i=1; i<n; i++) {
      if(arr[i] - wifi >= mid) {
        cc++;
        wifi = arr[i];
      }
    }

    if(cc < c)
      r = mid-1;
    else {
      if(mid > ans)
        ans = mid;
      l = mid+1;
    }
  }
  return ans;
}

int main() {
  cin >> n >> c;

  for(int i=0; i<n; i++) {
    cin >> *(arr+i);
  }

  sort(arr, arr+n);

  ll max = arr[n-1] - arr[0];
  cout << binarysearch(0, max) << '\n';

  return 0;
}
