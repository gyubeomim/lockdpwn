




















#include <cstdio>
#include <iostream>

using namespace std;

int d[1001];

int main(int argc, char const *argv[]) {
  int n;
  cin >> n;

  d[0] = 1;
  d[1] = 1;

  for(int i=2; i<=n; i++) {
    d[i] = d[i-1] + d[i-2];
    d[i] %= 10007;
  }

  cout << d[n] << '\n';

  return 0;
}
