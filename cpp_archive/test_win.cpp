
































#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MOD = 1e6;

int d[100001];
int A[100001];

int main(int argc, char const *argv[]) {
  string str;
  cin >> str;

  int n = str.size();

  for(int i=1; i<=n; i++) {
    A[i] = str.at(i-1) - '0';
  }

  if (A[1] != 0)
    d[1] = 1;
  if (10 <= A[1] * 10 + A[2] && A[1] * 10 + A[2] <= 26)
    d[2] = 1;

  for(int i=2; i<=n; i++) {
    if (A[i - 1] > 0)
      d[i] += d[i - 1];

    if (10 <= A[i - 1] * 10 + A[i] && A[i - 1] * 10 + A[i] <= 26)
      d[i] += d[i - 2];

    d[i] %= MOD;
  }

  cout << d[n] % MOD << '\n';

  return 0;
}