/*
 * #+DESCRIPTION:  백준 1158, 조세퍼스 문제를 푼 정답 코드
 * #+CATEGORY:     Queue
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초, 큐덱문자열
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <queue>
using namespace std;

int main() {
  int n,m;
  cin >> n >> m;

  queue<int> q;
  for(int i=0; i<n; i++) {
    q.push(i+1);
  }

  cout << "<";
  for(int i=0; i<n-1; i++) {
    for(int j=0; j<m-1; j++) {
        q.push(q.front());
        q.pop();
    }
    cout << q.front() << ", ";
    q.pop();
  }
  cout << q.front() << ">" << endl;

  return 0;
}
