
























#include<iostream>
#include<cstdio>

using namespace std;

int abs(int a) {
  return a < 0 ? -a : a;
}

int main() {
  int N,i,j,k;
  cin >> N;

  for (i = 1; i < N * 2; i++) {
    for (j = 0; j < abs(N - i); j++)
      cout << " ";
    for (k = 0; k < N - j; k++)
      cout << "*";
    cout << '\n';
  }

  return 0;
}

