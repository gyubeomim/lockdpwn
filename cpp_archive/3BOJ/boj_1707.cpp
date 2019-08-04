/*
 * #+DESCRIPTION:  백준 1707, 이분 그래프 문제를 푼 정답코드
 * #+CATEGORY:     GRAPH, SEARCH
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 그래프1 그래프 문제풀이
 * #+DATE:         2018-06-19-화
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

vector<int> a[20001];
int color[20001];

void dfs(int node, int c) {
  color[node] = c;

  for(int i=0; i<a[node].size(); i++) {
    int next = a[node][i];
    if(color[next] == 0) {
      dfs(next, 3-c);
    }
  }
}

int main() {
  int t;
  cin >> t;

  while(t--) {
    int n,m;
    cin >> n >> m;

    for(int i=1; i<=n; i++) {
      a[i].clear();
      color[i] = 0;
    }

    for(int i=0; i<m; i++) {
      int u,v;
      cin >> u >> v;
      a[u].push_back(v);
      a[v].push_back(u);
    }

    for(int i=1; i<=n; i++)
      if(color[i] == false)
        dfs(i,1);

    // ed: 모든 간선에 대해서 색을 비교해주는 코드
    bool ok = true;
    for(int i=1; i<=n; i++) {
      for(int k=0; k<a[i].size(); k++) {
        int j = a[i][k];
        if(color[i] == color[j]) {
          ok = false;
        }
      }
    }
    string ans = ok?"YES":"NO";
    cout << ans << '\n';
  }

  return 0;
}
