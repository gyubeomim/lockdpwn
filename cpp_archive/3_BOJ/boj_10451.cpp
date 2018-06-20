/*
 * #+DESCRIPTION:  백준 10451, 순열사이클 문제를 푼 정답코드, dfs를 사용해 연결요소의 개수를 세는 방식으로 문제를 풀었다
 * #+CATEGORY:     GRAPH, SEARCH
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 그래프1 그래프 문제풀이
 * #+DATE:         2018-06-19-화
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
using namespace std;

int a[1001];
bool check[1001];

void dfs(int node) {
  if(check[node] == true)
    return;

  check[node] = true;
  dfs(a[node]);
}

int main() {
  int t;
  cin >> t;

  while(t--) {
    int n;
    cin >> n;

    for(int i=1; i<=n; i++) {
      cin >> a[i];
      check[i] = false;
    }

    int ans = 0;
    for(int i=1; i<=n; i++) {
      if(check[i] == false) {
        dfs(i);
        ans += 1;
      }
    }
    cout << ans << '\n';
  }
  return 0;
}
