/*
 * #+DESCRIPTION:  백준 11650, 좌표 정렬하기 문제를 푼 정답코드, pair를 사용해서 문제를 풀었다
 * #+CATEGORY:     sort
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 정렬
 * #+DATE:         2018-06-18-월
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;

  vector<pair<int, int>> a(n); // ed: pair를 사용해서 문제를 풀었다

  for(int i=0; i<n; i++) {
    scanf("%d %d", &a[i].first, &a[i].second);
  }

  sort(a.begin(), a.end());

  for(int i=0; i<a.size(); i++)
    printf("%d %d\n", a[i].first, a[i].second);

  return 0;
}
