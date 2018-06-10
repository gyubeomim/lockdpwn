/*
 * +description:
 *  백준 9012, 괄호 문제를 푼 정답 코드
 *            스택의 성격을 이용해 푼 코드
 *
 *  code from [boj 알고리즘기초 스택]
 *
 * +author: Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
using namespace std;

// ed: 스택의 특성을 이용해 '(' 를 스택에 넣고 ')' 가 나올때마다 제거해서
//     valid한지를 판단하는 함수
string valid(string s) {
  int cnt=0;
  for(int i=0; i<s.size(); i++) {
    if(s[i] == '(') cnt++;
    else cnt--;

    if(cnt<0) return "NO";
  }

  if(cnt==0) return "YES";
  else return "NO";
}

int main() {
  int t;
  cin >> t;

  while(t--) {
    string s;
    cin >> s;
    cout << valid(s) << endl;
  }

  return 0;
}
