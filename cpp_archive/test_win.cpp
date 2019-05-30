





















#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using LL = long long;

LL d[100001];
LL A[100001];

int main(int argc, char const *argv[]) {
  int T,n;
  cin >> T;

  int t = 1;

  d[1] = 1;
  d[2] = 1;
  d[3] = 1;
  d[4] = 2;
  d[5] = 2;

  while(t <= T) {
    cin >> n;

    for (int i = 6; i <= n; i++) {
      d[i] = d[i - 1] + d[i - 5];
    }

    cout << d[n] << '\n';

    t += 1;
  }

  return 0;
}

