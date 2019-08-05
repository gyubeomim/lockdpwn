/*
 * #+DESCRIPTION:  백준 2447, 별찍기10 문제를 푼 코드
 * #+CATEGORY:     Divide & Conquer
 * #+LEVEL:        -
 * #+FROM:         중급1 분할정복 part 2
 * #+DATE:         2018-06-23-토
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define BLANK 0
#define STAR 1

void go(char **a, int x, int y, int n, int color) {
  int newColor;

  if(color == BLANK) {
    for(int i=x; i<x+n; i++) {
      for(int j=y; j<y+n; j++) {
        a[i][j] = ' ';
      }
    }
  }
  else {
    if(n==1)
      a[x][y] = '*';
    else {
      newColor = STAR;
      int m = n/3;

      for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
          if(i==1 && j==1)
            newColor = BLANK;
          else
            newColor = STAR;
          go(a, x+m*i, y+m*j, m, newColor);
        }
      }
    }
  }

}

int main() {
  int n;
  cin >> n;

  // ed: 2차원 배열은 아래와 같이 동적할당을 받는다
  char **a;
  a = (char **)malloc(sizeof(char *)*n);
  for(int i=0; i<n; i++) {
    a[i] = (char *)malloc(sizeof(char)*(n+1)); // ed: null 문자까지 받기 위해서 n+1
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<n+1; j++) {
      a[i][j] = 0;
    }
  }

  go(a,0,0,n,STAR);
  for(int i=0; i<n; i++) {
    cout << a[i] << '\n';
  }

  return 0;
}
