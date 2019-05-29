





















#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using LL = long long;

LL d[100001];
LL A[100001];

int main(int argc, char const *argv[]) {
  int n;
  cin >> n;

  for(int i=0; i<n; i++) {
    cin >> A[i];
  }


  d[0] = A[0];

  for(int i=1; i<n; i++) {
    d[i] = std::max(d[i], d[i - 1] + A[i]);
  }

  cout << *std::max_element(d, d+n-1) << '\n';

  return 0;
}

