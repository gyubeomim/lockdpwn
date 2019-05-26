




















#include <cstdio>
#include <iostream>

using namespace std;

using LL = long long;

LL d[1001][10];


int main(int argc, char const *argv[]) {
  int n;
  cin >> n;

  d[1][0] = 0;
  d[1][1] = 1;

  for (int i = 2; i <= n; i++) {
    for (int j = 0; j <= 1; j++) {
        if (j == 0)
          d[i][0] = d[i - 1][0] + d[i-1][1];
        else {
          d[i][1] = d[i-1][0]; 
      }
    }
  }

  LL result = 0;
  for (int i = 0; i <= 9; i++) {
    result += d[n][i];
  }

  cout << result << '\n';

  return 0;
}
