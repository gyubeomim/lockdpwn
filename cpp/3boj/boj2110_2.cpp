/*
 * #+DESCRIPTION:  백준 2110, 공유기 설치 문제를 푼 정답코드
 * #+CATEGORY:     Binary Search
 * #+LEVEL:        -
 * #+FROM:         http://codersbrunch.blogspot.kr/2016/11/2110.html
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <algorithm>

using namespace std;
int N,C,x[2000];

int main(int argc, char **argv) {
  cin >> N >> C;
  for(int i=0; i<N; i++) {
    cin >> *(x+i);
  }
  sort(x, x+N);

  int lower=1;
  int upper=x[N-1]+1;
  int limit;

  while(lower <= upper) {
    limit = (lower+upper)/2;
    int cnt = 1;
    int t=x[0];

    for(int i=1; i<N; i++) {
      if(x[i]-t >= limit)
        t = x[i], cnt++;
    }
    cnt < C ? upper=limit-1 : lower=limit+1; // ed: 삼항연산자 사용
  }
  cout << upper << endl;

  return 0;
}
