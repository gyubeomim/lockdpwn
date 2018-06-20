/*
 * #+DESCRIPTION:  백준 11724, 연결요소의 개수 문제를 푼 정답코드, DFS를 사용해서 문제를 풀었다
 * #+CATEGORY:     GRAPH, SEARCH
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 그래프1 그래프 문제풀이
 * #+DATE:         2018-06-19-화
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

vector<int> a[1001];
bool check[1001];

void dfs(int node) {
  check[node] = true;

  for(int i=0; i<a[node].size(); i++) {
    int next = a[node][i];
    if(check[next] == false)
      dfs(next);
  }
}

int main() {
  int n,m;
  cin >> n >> m;

  for(int i=0; i<m; i++) {
    int u,v;
    cin >> u >> v;
    a[u].push_back(v);
    a[v].push_back(u);
  }

  // ed: 아직 방문하지 않은 노드를 dfs를 돌려서 연결요소의 개수를 구한다
  int components = 0;
  for(int i=1; i<=n; i++) {
    if(check[i] == false) {
      dfs(i);
      components += 1;
    }
  }

  cout << components << '\n';
  return 0;
}
