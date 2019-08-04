/*
 * #+DESCRIPTION:      백준 2261, 가장 가까운 두 점 찾기 문제를 푼 코드
 * #+CATEGORY:         Divide & Conquer
 * #+TIME_COMPLEXITY:  O(N(logN)^2)
 * #+LEVEL:            -
 * #+FROM:             중급1 분할정복 part 2
 * #+DATE:             2018-06-23-토
 * #+AUTHOR:           Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
  int x;
  int y;

  Point(){}
  Point(int x, int y) :x(x),y(y) {}
  bool operator <(const Point &v) const {
    if(x == v.x)
      return y < v.y;
    else
      return x < v.x;
  }
};

bool cmp_y(const Point &u, const Point &v) {
  return u.y < v.y;
}

int dist(Point p1, Point p2) {
  return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
}

int brute_force(vector<Point> &a, int x, int y) {
  int ans = -1;
  for(int i=x; i<=y-1; i++) {
    for(int j=i+1; j<=y; j++) {
      int d = dist(a[i], a[j]);
      if(ans == -1 || ans > d)
        ans = d;
    }
  }
  return ans;
}

int closest(vector<Point> &a, int start, int end) {
  int n = end - start + 1;

  // ed: n이 3보다 작은 경우 모든 경우의 수를 찾아본다
  if(n <= 3)
    return brute_force(a,start,end);

  int mid = (start+end)/2;
  int d_left = closest(a, start, mid);
  int d_right = closest(a, mid+1, end);

  // 임시로 min(Dl, Dr) 값을 구한다
  int ans = min(d_left, d_right);

  // ed: 중간을 기준으로 두 점 사이의 거리가 ans인 점들만 따로 추려낸다
  vector<Point> b;
  for(int i=start; i<=end; i++) {
    int d = a[i].x - a[mid].x;
    if(d*d < ans)
      b.push_back(a[i]);
  }

  // ed: b를 y값을 기준으로 정렬한다
  sort(b.begin(), b.end(), cmp_y);
  int m = b.size();

  for(int i=0; i<m-1; i++) {
    for(int j=i+1; j<m; j++) {
      int y= b[j].y - b[i].y;
      if(y*y < ans) {
        int d = dist(b[i], b[j]);
        if(d < ans)
          ans = d;
      }
      else break;   // ed: break 구문이 없으면 순수 O(N^2) 이지만 break가 존재하므로 계산횟수가 매우 줄어든다
    }
  }
  return ans;
}

int main() {
  int n;
  cin >> n;
  vector<Point> a(n);

  for(int i=0; i<n; i++) {
    scanf("%d %d", &a[i].x, &a[i].y);
  }

  sort(a.begin(), a.end());
  cout << closest(a, 0, n-1) << '\n';

  return 0;
}
