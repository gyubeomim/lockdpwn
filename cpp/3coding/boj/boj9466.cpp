/*
 * #+DESCRIPTION:  백준 9466, 텀 프로젝트
 * #+CATEGORY:     GRAPH
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 그래프1 그래프 문제풀이
 */
#include <cstdio>
#include <iostream>
using namespace std;

int a[100001];
int check[100001];
int s[100001];
int n;

int dfs(int x, int cnt, int &step) {
  if(check[x] != 0) {
    if(step != s[x]) {  // ed: 이미 DFS를 해서 완료된 노드를 방문하는 경우
      return 0;
    }
    return cnt - check[x];
  }

  check[x] = cnt;
  s[x] = step;
  return dfs(a[x], cnt+1, step);
}

int main() {
  int t;
  cin >> t;

  while(t--) {
    cin >> n;

    for(int i=1; i<=n; i++) {
      cin >> a[i];
      check[i] = 0;
      s[i] = 0;
    }

    int ans = 0;
    for(int i=1; i<=n; i++) {
      if(check[i] == 0)
        ans += dfs(i, 1, i);
    }
    cout << n - ans << '\n';
  }
  return 0;
}
