#include <cstring>
#include <iostream>

using namespace std;

using ll = long long;

ll n,m,tree[1000001] = {0};

int main() {
  ll lo = 0;
  ll hi = 10000000000001;

  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    ll x;
    cin >> x;
    tree[i] = x;
  }

  while (lo < hi) {
    ll mid = (lo + hi) >> 1;
    ll result = 0;

    for (int i = 0; i < n; i++) {
      ll val = tree[i]-mid;
      if(val>0)
        result += val;
    }
    if (result >= m) lo = mid + 1;
    else hi = mid;
  }
  cout << lo - 1 << '\n';

  return 0;
}