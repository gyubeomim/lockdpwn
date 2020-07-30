/*
 * #+DESCRIPTION:  백준 10799, 쇠막대기 문제를 푼 정답 코드
 * #+CATEGORY:     stack
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초, 스택
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <stack>

using namespace std;

int main() {
  string a;
  cin >> a;

  int n = a.size();
  int ans=0;
  stack<int> s;

  for(int i=0; i<n; i++) {
    // 여는괄호 (
    if(a[i] == '(')
      s.push(i); // index를 스택에 삽입한다
    // 닫는괄호 )
    else {
      // index 차이가 1이 나면 레이저이므로 ans에 현재 스택의 크기만큼 더한다
      if(s.top()+1 == i) {
        s.pop();
        ans += s.size();
      }
      // index 차이가 1 이상이 나면 레이저가 아니고 ans에 1만큼 더한다
      else {
        s.pop();
        ans += 1;
      }
    }
  }
  cout << ans << endl;

  return 0;
}
