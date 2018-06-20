/*
 * #+DESCRIPTION:  백준 1707, 이분 그래프 문제를 푼 정답코드, bool dfs() 함수를 사용해서 dfs() 함수 내에서 이분그래프를 판별하는 코드 추가
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

// ed: bool 형식을 return 함으로써 이분그래프인지 아닌지 검사하는 코드가 추가된 함수
bool dfs(int node, int c) {
  color[node] = c;

  for(int i=0; i<a[node].size(); i++) {
    int next = a[node][i];
    if(color[next] == false) {
      if(dfs(next, 3-c) == false)
        return false;
    }
    else if(color[next] == color[node]) {
      return false;
    }
  }
  return true;
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

    // ed: bool dfs() 함수로 인해 아래 코드들이 간결해졌다
    bool ok = true;
    for(int i=1; i<=n; i++) {
      if(color[i] == false)
        if(dfs(i,1) == false)
          ok = false;
    }
    string ans = ok ? "YES":"NO";
    cout << ans << '\n';
  }

  return 0;
}
