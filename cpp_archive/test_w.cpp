#include <cstring>
#include <iostream>

using namespace std;

using ll = long long;


int main() {
  ll lan[1000001] = {0};
  ll lo = 0;
  ll hi = 10000000000001;

  ll k, n;
  cin >> k >> n;

  for (int i = 0; i < k; i++) {
    int x;
    cin >> x;
    lan[i] = x;
  }


  while (lo < hi) {
    ll mid = (lo + hi) >> 1;
    ll result = 0;

    for (int i = 0; i < k; i++) {
      result += lan[i] / mid;
    }
    if (result >= n)
      lo = mid + 1;
    else
      hi = mid;
  }
  cout << lo - 1 << '\n';

  return 0;
}