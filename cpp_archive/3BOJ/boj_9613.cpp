/*
 * #+DESCRIPTION:  백준 9613, GCD 합 문제를 푼 정답코드
 * #+CATEGORY:     수학
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 수학1
 * #+DATE:         2018-06-12-화
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
using namespace std;

int gcd(int x, int y) {
  if(y==0) return x;
  else return gcd(y, x%y);
}


int main() {
  int t;
  cin >> t;

  while(t--) {
    int a[111] = {-1};
    int n;
    cin >> n;

    for(int i=0; i<n; i++) {
      cin >> a[i];
    }

    long long sum = 0; // ed: long long 타입이어야 한다

    for(int i=0; i<n; i++) {
      for(int j=i; j<n; j++) {
        if(i != j)
          sum += gcd(a[i],a[j]);
      }
    }
    cout << sum << endl;
  }
  return 0;
}
