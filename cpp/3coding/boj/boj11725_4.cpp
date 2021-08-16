/*
 * #+DESCRIPTION:  백준 11725, 트리의 부모 찾기 문제를 푼 코드, BFS를 사용해서 문제를 풀었다
 * #+CATEGORY:     TREE, BFS
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 트리1 트리의 순회
 * #+DATE:         2018-06-20-수
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = 100001;
vector<int> a[MAX];
int parent[MAX];
bool check[MAX];
int depth[MAX];

int main() {
  int n;
  cin >> n;

  for(int i=0; i<n-1; i++) {
    int u,v;
    scanf("%d %d", &u, &v);
    a[u].push_back(v);
    a[v].push_back(u);
  }

  // ed: 1번 노드는 부모가 없고 이미 방문했으므로 true
  depth[1] = 0;
  check[1] = true;

  // ed: BFS를 수행한다
  queue<int> q;
  q.push(1);
  parent[1] = 0;
  while(!q.empty()) {
    int x = q.front();
    q.pop();
    for(int y : a[x]) {
      if(!check[y]) {
        depth[y] = depth[x] + 1;
        check[y] = true;
        parent[y] = x;
        q.push(y);
      }
    }
  }

  for(int i=2; i<=n; i++) {
    cout << parent[i] << '\n';
  }

  return 0;
}
