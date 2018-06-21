/*
 * #+DESCRIPTION:  백준 1931, 회의실배정 문제를 푼 코드, 그리디 알고리즘을 사용해 문제를 풀었다
 * #+CATEGORY:     GREEDY
 * #+LEVEL:        -
 * #+FROM:         중급1 그리디 알고리즘 part 1
 * #+DATE:         2018-06-21-목
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Meeting {
  int begin;
  int end;
};


bool cmp(const Meeting &u, const Meeting &v) {
  if(u.end == v.end)
    return u.begin < v.begin;
  else
    return u.end < v.end;
}

int main() {
  int n;
  cin >> n;
  vector<Meeting> a(n);

  for(int i=0; i<n; i++) {
    scanf("%d %d", &a[i].begin, &a[i].end);
  }

  sort(a.begin(), a.end(), cmp);

  int now=0;
  int ans=0;
  for(int i=0; i<a.size(); i++) {
    if(now <= a[i].begin ) { // ed: 회의가 끝나는 순서대로 ans++ 를 하는 greedy 알고리즘
      now = a[i].end;
      ans += 1;
    }
  }
  cout << ans << '\n';

  return 0;
}
