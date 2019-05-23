










































#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int N;
  cin >> N;

  for(int i=1; i<=2*N-1; i++) {
    cout.width(N-i+1);
    for(int j=1; j<=2*i-1; j++) {
      cout << "*";
    }
    cout << '\n';
  }

  return 0;
}
