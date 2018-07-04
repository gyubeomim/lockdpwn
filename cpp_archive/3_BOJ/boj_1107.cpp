/*
 * #+DESCRIPTION:       백준 1107, 리모컨 문제를 푼 코드
 * #+CATEGORY:          BRUTE FORCE
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              중급1 완전탐색1 그냥다해보기
 * #+DATE:              2018-06-25-월
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <iostream>
using namespace std;

bool broken[10];  // ed: 버튼이 망가져있으면 true, 아니면 false

int possible(int c) {
  if(c==0) {
    if(broken[0])
      return 0;
    else
      return 1;
  }

  int len = 0;
  while(c > 0) {
    if(broken[c%10])
      return 0;

    len += 1;
    c /= 10;
  }
  return len;
}

int main() {
  int n;
  cin >> n;
  int m;
  cin >> m;

  for(int i=0; i<m; i++) {
    int x;
    cin >> x;
    broken[x] = true;
  }

  int ans = n - 100;   // ed: 기본채널 100 과의 차이를 최소 ans로 설정한다

  if(ans < 0)
    ans = -ans;

  for(int i=0; i<=1000000; i++) { // ed: 숫자버튼으로 이동하는 채널
    int c=i;
    int len = possible(c);  // ed: 길이를 잰다

    if(len > 0) {
      int op = c - n;       // ed: +,-를 몇 번 눌러야 하는지 계산
      if(op < 0)
        op = -op;           // ed: +를 누르는 경우
      if(ans > len + op)
        ans = len + op;
    }
  }
  cout << ans << '\n';
  return 0;
}
