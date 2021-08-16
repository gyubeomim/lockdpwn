/*
 * #+DESCRIPTION:  백준 1260, DFS와 BFS
 * #+CATEGORY:     GRAPH, SEARCH
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 그래프1 그래프의 표현
 */
#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
  int from;
  int to;
};

Edge edge[20001];
int cnt[1001];
bool check[1001];

bool cmp(const Edge &u, const Edge &v) {
  if(u.from == v.from ) {
    return u.to < v.to;
  }
  else {
    return u.from < v.from;
  }
}

void dfs(int node) {
  check[node] = true;
  cout << node << " ";

  for(int i=cnt[node-1]; i<cnt[node]; i++) {
    int next = edge[i].to;
    if(check[next] == false)
      dfs(next);
  }
}

void bfs(int start) {
  queue<int> q;
  q.push(start);
  check[start] = true;

  while(!q.empty()) {
    int node = q.front();
    q.pop();
    cout << node << " ";

    for(int i=cnt[node-1]; i<cnt[node]; i++) {
      int next = edge[i].to;
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
    cin >> edge[i].from >> edge[i].to;
    edge[i+m].from = edge[i].to;
    edge[i+m].to = edge[i].from;
  }
  m *= 2;
  sort(edge, edge+m, cmp);

  for(int i=0; i<m; i++)
    cnt[edge[i].from] += 1;

  // ed: 간선의 누적합을 구하는 코드
  for(int i=1; i<=n; i++)
    cnt[i] += cnt[i-1];

  dfs(start);
  puts("");
  memset(check, false, sizeof(check));
  bfs(start);
  puts("");

  return 0;
}
