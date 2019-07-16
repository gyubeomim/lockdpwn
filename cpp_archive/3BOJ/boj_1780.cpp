/*
 * #+DESCRIPTION:  백준 1780, 종이의 개수 문제를 푼 코드
 * #+CATEGORY:     Divide & Conquer
 * #+LEVEL:        -
 * #+FROM:         중급1 분할정복 part 1
 * #+DATE:         2018-06-21-목
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
using namespace std;

int a[3000][3000];
int cnt[3];

// ed: [x,y] [x+n, y+n] 사이의 값이 전부 같은지 확인하는 함수
bool same(int x, int y, int n) {
  for(int i=x; i<x+n; i++) {
    for(int j=y; j<y+n; j++) {
      if(a[x][y] != a[i][j])
        return false;
    }
  }
  return true;
}

void solve(int x, int y, int n) {
  if (same(x,y,n)) {
    cnt[a[x][y]+1] += 1;
    return;
  }

  // ed: 분할정복을 수행한다
  int m = n/3;
  for(int i=0; i<3; i++) {
    for(int j=0; j<3; j++) {
      solve(x+i*m, y+j*m, m);
    }
  }
}

int main() {
  int n;
  cin >> n;

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> a[i][j];
    }
  }

  // ed: [0,0] 부터 n개만큼 값이 같은지 검사한다
  solve(0,0,n);

  for(int i=0; i<3; i++) {
    cout << cnt[i] << '\n';
  }

  return 0;
}
