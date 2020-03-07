/*
 * #+DESCRIPTION:  백준 4963, 섬의 개수 문제를 푼 코드, BFS를 사용해서 dx,dy[8] 방향에 대해서 탐색하면서 문제를 풀었다
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

int a[100][100];
int d[100][100];
int dx[] = {0,0,1,-1,1,1,-1,-1};  // ed: 대각선방향까지 고려한다
int dy[] = {1,-1,0,0,1,-1,1,-1};
int n,m;

void bfs(int x, int y, int cnt ) {
  queue<pair<int,int>> q;
  q.push(make_pair(x,y));
  d[x][y] = cnt;

  while(!q.empty()) {
    x = q.front().first;
    y = q.front().second;
    q.pop();

    for(int k=0; k<8; k++) {
      int nx = x + dx[k];
      int ny = y + dy[k];

      if(nx>=0 && nx<n && ny>=0 && ny<m)
        if(a[nx][ny] == 1 && d[nx][ny]==0) {
          q.push(make_pair(nx,ny));
          d[nx][ny] = cnt;
        }
    }
  }
}

int main() {
  while(true) {
    cin >> m >> n;
    if(n == 0 && m == 0) break;

    for(int i=0; i<n; i++) {
      for(int j=0; j<m; j++) {
        scanf("%1d", &a[i][j]);
        d[i][j] = 0;
      }
    }

    int cnt=0;
    for(int i=0; i<n; i++) {
      for(int j=0; j<m; j++) {
        if(a[i][j] == 1 && d[i][j] == 0)
          bfs(i, j, ++cnt);
      }
    }
    cout << cnt << '\n';
  }
  return 0;
}
