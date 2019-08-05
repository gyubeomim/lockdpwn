/*
 * #+DESCRIPTION:  백준 1373, 2진수 8진수 문제를 푼 정답코드
 * #+CATEGORY:     수학, 진법변환
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 수학1
 * #+DATE:         2018-06-12-화
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
  string s;
  cin >> s;

  int n = s.size();
  if(n%3 == 1)
    cout << s[0];
  else if(n%3 == 2)
    cout << (s[0]-'0')*2 + (s[1]-'0');

  for(int i=n%3; i<n; i+=3) {
    cout << (s[i]-'0')*4 + (s[i+1]-'0')*2 + (s[i+2]-'0');
  }
  cout << endl;

  return 0;
}
