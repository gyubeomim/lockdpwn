/*
 * #+DESCRIPTION:  백준 7576, 토마토 문제를 푼 코드, BFS를 사용해서 문제를 풀었다
 * #+CATEGORY:     GRAPH, BFS
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 그래프1 그래프 문제풀이
 * #+DATE:         2018-06-20-수
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int a[1000][1000];
int d[1000][1000];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

int main() {
  int n,m;
  cin >> m >> n;

  queue<pair<int,int>> q;

  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> a[i][j];
      d[i][j] = -1;

      if(a[i][j]==1) {
        q.push(make_pair(i,j));
        d[i][j] = 0;
      }
    }
  }

  while(!q.empty()) {
    int x = q.front().first;
    int y = q.front().second;
    q.pop();

    for(int k=0; k<4; k++) {
      int nx = x+dx[k];
      int ny = y+dy[k];

      if(nx>=0 && nx<n && ny>=0 && ny<m) {
        if(a[nx][ny] == 0 && d[nx][ny] == -1) {
          d[nx][ny] = d[x][y] + 1;
          q.push(make_pair(nx,ny));
        }
      }
    }
  }

  int ans = 0;
  // ed: 모두 탐색했을 때까지 걸린 최대값을 출력한다
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      if(ans < d[i][j])
        ans = d[i][j];
    }
  }

  // ed: 방문하지 않은 노드가 하나라도 있는 경우 -1을 출력한다
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      if(a[i][j] == 0 && d[i][j] == -1)
        ans = -1;
    }
  }
  cout << ans << '\n';

  return 0;
}
