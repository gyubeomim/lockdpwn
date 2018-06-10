/*
 * +description:
 *  백준 1406, 에디터 문제를 푼 정답 코드
 *            스택을 사용해 문제를 풀었다
 *
 *  code from [boj 알고리즘기초, 스택]
 * +author: Edward Im (gyurse@gmail.com)
 *
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
using namespace std;

char a[600000];

int main() {
  cin >> a;
  stack<char> left, right;

  int n = strlen(a);
  for(int i=0; i<n; i++)
    left.push(a[i]);

  int m;
  cin >> m;
  while(m--) {
    char what;
    scanf(" %c", &what);

    // 각각의 명령어에 따라 left, right 스택의 데이터를 옮긴다
    if(what == 'L') {
      if(!left.empty()) {
        right.push(left.top());
        left.pop();
      }
    }
    else if(what == 'D') {
      if(!right.empty()) {
        left.push(right.top());
        right.pop();
      }
    }
    else if(what == 'B') {
      if(!left.empty()) {
        left.pop();
      }
    }
    else if(what == 'P') {
      char c;
      scanf(" %c", &c);
      left.push(c);
    }
  }

  // 데이터를 출력하기 위해 left의 데이터를 전부 right로 옮긴다
  while(!left.empty()) {
    right.push(left.top());
    left.pop();
  }
  // 데이터 출력
  while(!right.empty()) {
    cout << right.top() ;
    right.pop();
  }
  cout << endl;
  return 0;
}
