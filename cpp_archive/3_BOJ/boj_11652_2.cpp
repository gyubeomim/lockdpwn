/*
 * #+DESCRIPTION:  백준 11652, 카드 문제를 푼 정답코드, map<long long, int>를 사용해 문제를 풀었다
 * #+CATEGORY:     sort
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 정렬
 * #+DATE:         2018-06-19-화
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

int main() {
  int n;
  cin >> n;
  map<long long, int> d;

  while(n--) {
    long long x;
    cin >> x;
    d[x] += 1;
  }

  int m = 0;
  long long ans = 0;

  for(auto &p : d) {
    if(p.second > m) {
      m = p.second;
      ans = p.first;
    }
    else if(p.second == m && p.first < ans ) {
      ans = p.first;
    }
  }
  cout << ans << '\n';

  return 0;
}
