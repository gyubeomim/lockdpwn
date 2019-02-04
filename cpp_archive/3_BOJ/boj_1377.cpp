/*
 * #+DESCRIPTION:  백준 1377, 버블소트 문제를 푼 정답코드
 * #+CATEGORY:     sort
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 정렬
 * #+DATE:         2018-06-19-화
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<pair<int,int>> a(n);

  for(int i=0; i<n; i++) {
    cin >> a[i].first;
    a[i].second = i;
  }

  sort(a.begin(), a.end());
  int ans=0;

  // ed: 입력시 인덱스 - 정렬된 인덱스 값을 계산해서 몇단계로 버블소트가 구성되어 있는지 계산한다
  for(int i=0; i<n; i++) {
    if(ans < a[i].second - i)
      ans = a[i].second - i;
  }
  cout << ans + 1 << '\n';

  return 0;
}
