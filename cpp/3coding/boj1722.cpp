/*
 * #+DESCRIPTION:       백준 1722, 순열의 순서
 * #+CATEGORY:          PERMUTATION
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              중급1 순열
 */
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

long long f[21] = {1};
bool c[21];

int main() {
  for(int i=1; i<=20; i++)
    f[i] = f[i-1] * i;

  int n;
  cin >> n;

  int what;
  cin >> what;

  if(what == 2) {  // ed: 두번째줄 첫번째 숫자가 2인 경우 순열을 입력받고
    vector<int> a(n);
    for(int i=0; i<n; i++)
      cin >> a[i];

    long long ans = 0;

    for(int i=0; i<n; i++) {
      for(int j=1; j<a[i]; j++) {
        if(c[j] == false)
          ans += f[n-i-1];
      }
      c[a[i]] = true;
    }
    cout << ans+1 << '\n';
  }
  else if(what == 1) {  // ed: 1인 경우 순열의 숫자를 입력받는다
    long long k;
    cin >> k;
    vector<int> a(n);

    for(int i=0; i<n; i++) {
      for(int j=1; j<=n; j++) {
        if(c[j] == true) continue;
        if(f[n-i-1] < k)
          k -= f[n-i-1];
        else {
          a[i] = j;
          c[j] = true;
          break;
        }
      }
    }
    for(int i=0; i<n; i++) {
      cout << a[i] << ' ';
    }
    cout << '\n';
  }

  return 0;
}
