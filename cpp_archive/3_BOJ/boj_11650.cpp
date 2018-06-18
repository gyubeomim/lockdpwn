/*
 * #+DESCRIPTION:  백준 11650, 좌표 정렬하기 문제를 푼 정답코드, 연산자 오버로딩을 사용해 문제를 풀었다
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

  // ed: 연산자 오버로딩
  bool operator <(const Point &v) const {
    if(x < v.x) return true;
    else if(x == v.x) return y < v.y;
    else return false;
  }
};

int main() {
  int n;
  cin >> n;
  vector<Point> a(n);

  for(int i=0; i<n; i++)
    scanf("%d %d", &a[i].x , &a[i].y);

  // ed: struct에서 연산자 오버로딩을 했으므로 3번째 파라미터가 필요없다
  sort(a.begin(), a.end());

  for(int i=0; i<a.size(); i++)
    printf("%d %d\n", a[i].x, a[i].y);


  return 0;
}
