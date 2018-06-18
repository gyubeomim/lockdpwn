/*
 * #+DESCRIPTION:  백준 11650, 좌표 정렬하기 문제를 푼 정답코드, cmp 함수를 따로 정의해서 sort의 3번째 파리미터로 사용해서 풀었다
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

struct Point {
  int x,y;
};

bool cmp(const Point &u, const Point &v) {
  if(u.x < v.x)
    return true;
  else if(u.x == v.x)
    return u.y < v.y;
  else
    return false;
}

int main() {
  int n;
  cin >> n;

  vector<Point> a(n);

  for(int i=0; i<n; i++)
    scanf("%d %d", &a[i].x, &a[i].y);

  sort(a.begin(), a.end(), cmp);

  for(int i=0; i<a.size(); i++)
    printf("%d %d\n", a[i].x, a[i].y);

  return 0;
}
