/*
 * #+DESCRIPTION:  백준 2331, 반복수열 문제를 푼 정답코드
 * #+CATEGORY:     GRAPH
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 그래프1 그래프 문제풀이
 * #+DATE:         2018-06-19-화
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
using namespace std;

int check[1000000];

// ed: 숫자 x를 p번 곱하는 함수
int pow(int x, int p) {
  int ans = 1;
  for(int i=0; i<p; i++) {
    ans = ans*x;
  }
  return ans;
}

// ed: 각 자리수를 추출해서 p번만큼 곱해서 리턴하는 함수
int next(int a, int p) {
  int ans = 0;
  while(a>0) {
    ans += pow(a%10, p);
    a /= 10;
  }
  return ans;
}

int length(int a, int p, int cnt) {
  if(check[a] != 0)
    return check[a] - 1;

  check[a] = cnt;
  int b = next(a, p);
  return length(b, p, cnt+1);
}

int main() {
  int a,p;
  cin >> a >> p;
  cout << length(a, p, 1) << '\n';

  return 0;
}
