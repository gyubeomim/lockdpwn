/*
 * #+DESCRIPTION:  백준 11728, 배열 합치기 문제를 푼 코드, Merge sort를 사용해서 문제를 풀었다
 * #+CATEGORY:     Divide & Conquer
 * #+LEVEL:        -
 * #+FROM:         중급1 분할정복 part 1
 * #+DATE:         2018-06-21-목
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
using namespace std;

int a[1000000];
int b[1000000];
int c[1000000];

int main() {
  int n,m;
  cin >> n >> m;

  for(int i=0; i<n; i++)
    cin >> a[i];

  for(int i=0; i<m; i++)
    cin >> b[i];


  int i=0;
  int j=0;
  int k=0;

  // ed: 이미 a[i], b[i]가 정렬되어 있으므로 Merge sort를 수행한다
  while(i < n && j < m) {
    if(a[i] <= b[j])
      c[k++] = a[i++];
    else
      c[k++] = b[j++];
  }

  while(i < n) {
    c[k++] = a[i++];
  }
  while(j < m) {
    c[k++] = b[j++];
  }

  for(int i=0; i<n+m; i++) {
    cout << c[i] << " ";
  }
  cout << '\n';

  return 0;
}
