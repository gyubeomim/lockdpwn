/*
 * #+DESCRIPTION:  백준 1992, 쿼드트리 문제를 푼 코드
 * #+CATEGORY:     Divide & Conquer, Tree, Quad Tree
 * #+LEVEL:        -
 * #+FROM:         중급1 분할정복 part 2
 * #+DATE:         2018-06-23-토
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
using namespace std;

int a[100][100];

bool same(int x, int y, int n)
  for(int i=x; i<x+n; i++) {
    for(int j=y; j<y+n; j++) {
      if(a[x][y] != a[i][j])
        return false;
    }
  }
  return true;
}

void solve(int x, int y, int n) {
  if(same(x,y,n))
    cout << a[x][y];
  else {
    cout << '(';
    int m = n/2;
    for(int i=0; i<2; i++) {
      for(int j=0; j<2; j++) {
        solve(x+m*i, y+m*j, m);
      }
    }
    cout << ')';
  }
}

int main() {
  int n;
  cin >> n;

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      scanf("%1d", &a[i][j]);
    }
  }
  solve(0,0,n);
  cout << '\n';

  return 0;
}
