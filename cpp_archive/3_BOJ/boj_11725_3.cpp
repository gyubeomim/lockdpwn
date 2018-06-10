/*
 * #+DESCRIPTION: 백준 11725, 트리의 부모 찾기 문제를 푼 정답 코드
 * #+CATEGORY:
 * #+LEVEL:        -
 * #+FROM:         http://debuglog.tistory.com/86
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <stack>

using namespace std;

int parent[100001] = {0};
int n,a,b;
stack<pair<int,int>> _stack[2];
int idx = 0;

int main(int argc, char **argv) {
  cin >> n;
  parent[1] = 1;

  for(int i=1; i<n; i++) {
    cin >> a >> b;
    if(parent[a])
      parent[b] = a;
    else if(parent[b])
      parent[a] = b;
    else
      _stack[idx].push({a,b});
  }

  while(!_stack[0].empty() || !_stack[1].empty()) {
    auto t = _stack[idx].top();
    a = t.first; b= t.second;
    _stack[idx].pop();

    if(parent[a])
      parent[b] = a;
    else if(parent[b])
      parent[a] = b;
    else
      _stack[1-idx].push({a,b});

    if(_stack[idx].empty())
      idx = 1-idx;
  }

  std::cout << "-------------------------------------" << endl;
  for(int i=2; i<=n; i++) {
    cout << parent[i] << endl;
  }

  return 0;
}
