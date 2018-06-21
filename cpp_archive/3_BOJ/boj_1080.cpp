/*
 * #+DESCRIPTION:  백준 1080, 행렬 문제를 푼 코드
 * #+CATEGORY:     GREEDY
 * #+LEVEL:        -
 * #+FROM:         중급1 그리디 알고리즘 part 2
 * #+DATE:         2018-06-21-목
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
using namespace std;

int a[50][50];
int b[50][50];

void flip(int x, int y) {
  for(int i=x-1; i<=x+1; i++) {
    for(int j=y-1; j<=y+1; j++) {
      a[i][j] = 1 - a[i][j];
    }
  }
}

int main() {
  int n,m;
  cin >> n >> m;

  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      scanf("%1d", &a[i][j]);
    }
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      scanf("%1d", &b[i][j]);
    }
  }

  // ed: 범위를 생각해서 [3x3]이므로 n-2,m-2 까지만 검사한다
  int ans=0;
  for(int i=0; i<n-2; i++) {
    for(int j=0; j<m-2; j++) {
      if(a[i][j] != b[i][j]) {
        ans += 1;
        flip(i+1, j+1);
      }
    }
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      if(a[i][j] != b[i][j]) {
        cout << "-1" << '\n';
        return 0;
      }
    }
  }
  cout << ans << '\n';
  return 0;
}
