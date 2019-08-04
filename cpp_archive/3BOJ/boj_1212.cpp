/*
 * #+DESCRIPTION:  백준 1212, 8진수 2진수 문제를 푼 정답코드
 * #+CATEGORY:     수학 진법변환
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 수학1
 * #+DATE:         2018-06-12-화
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

string eight[8]={"000","001","010","011","100","101","110","111"};

int main() {
  string s;
  cin >> s;

  bool start = true; // ed: 첫 글자인지 아닌지 검사하는 변수

  if(s.length() == 1 && s[0]-'0' == 0) // ed: 1 이 입력으로 들어온 경우
    cout << "0";

  for(int i=0; i < s.length(); i++) {
    int n = s[i]-'0';

    if(start == true && n < 4) {
      if(n == 0) continue;
      else if(n == 1) cout << "1";
      else if(n == 2) cout << "10";
      else if(n == 3) cout << "11";

      start = false;
    }
    else {
      cout << eight[n];
      start = false;
    }
  }
  return 0;
}
