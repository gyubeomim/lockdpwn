/*
 * #+DESCRIPTION:  백준 10989, 수 정렬하기3 문제를 푼 정답코드
 *                 N의 범위가 매우 크고 값이 1~10000까지 이므로
 *                 보통 방법으로는 풀 수 없고 cnt[10000] 변수를 사용해서 문제를 풀었다
 * #+CATEGORY:     sort
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 정렬
 * #+DATE:         2018-06-18-월
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
using namespace std;

int cnt[10001];

int main() {
  int n;
  cin >> n;
  int temp = 0;

  for(int i=0; i<n; i++) {
    cin >> temp;
    cnt[temp] += 1;
  }

  for(int i=1; i<=10000; i++) {
    if(cnt[i] > 0) {
      for(int j=0; j<cnt[i]; j++) {
        cout << i << '\n';
      }
    }
  }
  return 0;
}
