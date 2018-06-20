/*
 * #+DESCRIPTION:  백준 1260, DFS와 BFS 문제를 푼 정답코드, 비재귀적으로 문제를 풀었다
 * #+CATEGORY:     GRAPH, SEARCH
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 그래프1 그래프의 표현
 * #+DATE:         2018-06-19-화
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> a[1001];
bool check[1001];

void dfs(int node) {
  stack<pair<int, int>> s;
  s.push(make_pair(node,0));
  check[node] = true;
  cout << node << " ";

  while(!s.empty()) {
    int node = s.top().first;
    int start = s.top().second;
    s.pop();

    for(int i=start; i<a[node].size(); i++) {
      int next = a[node][i];
      if(check[next] == false) {
        cout << next << " ";
        check[next] = true;
        s.push(make_pair(node, i+1));
        s.push(make_pair(next, 0));
        break;
      }
    }
  }
}

void bfs(int start) {
  queue<int> q;
  memset(check, false, sizeof(check));
  check[start] = true;
  q.push(start);

  while(!q.empty()) {
    int node = q.front();
    q.pop();
    cout << node << " ";

    for(int i=0; i<a[node].size(); i++) {
      int next = a[node][i];
      if(check[next] == false) {
        check[next] = true;
        q.push(next);
      }
    }
  }
}

int main() {
  int n,m,start;
  cin >> n >> m >> start;
  for(int i=0; i<m; i++) {
    int u,v;
    cin >> u >> v;
    a[u].push_back(v);
    a[v].push_back(u);
  }

  for(int i=1; i<=n; i++) {
    sort(a[i].begin(), a[i].end());
  }

  dfs(start);
  puts("");
  bfs(strat);
  puts("");

  return 0;
}
