/*
 * #+DESCRIPTION:  백준 2146, 다리 만들기 문제를 푼 코드, 섬을 만들고 BFS를 사용해 1,2,3 순으로 거리를 확장해 나간 다음 두 섬 간의 거리가 가장 짧은 지점을 출력하는 식으로 문제를 풀었다
 * #+CATEGORY:     GRAPH, BFS
 * #+LEVEL:        -
 * #+FROM:         알고리즘기초 그래프1 그래프 문제풀이
 * #+DATE:         2018-06-20-수
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

int a[100][100];
int g[100][100];
int d[100][100];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};

int main() {
  int n;
  cin >> n;

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> a[i][j];
    }
  }

  int cnt=0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(a[i][j] == 1 && g[i][j] == 0) {
        g[i][j] == ++cnt;
        queue<pair<int,int>> q;
        q.push(make_pair(i,j));

        while(!q.empty()) {
          int x = q.front().first;
          int y = q.front().second;
          q.pop();

          for(int k=0; k<4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if(nx>=0 && nx<n && ny>=0 && ny<n) {
              if(a[nx][ny] == 1 && g[nx][ny] == 0) {
                g[nx][ny] = cnt;
                q.push(make_pair(nx,ny));
              }
            }
          }
        }
      }
    }
  }

  // ed: 섬을 그룹화 해놓은 다음 그 섬으로부터 BFS를 수행한다
  queue<pair<int,int>> q;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      d[i][j] = -1;
      if(a[i][j] == 1) {
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

      if(nx>=0 && nx<n && ny>=0 && ny<n) {
        if(d[nx][ny] == -1) {
          d[nx][ny] = d[x][y] + 1;  // ed: 매 루프마다 거리는 +1 이 되고
          g[nx][ny] = g[x][y];      // ed: 어떤 그룹인지도 표시한다
          q.push(make_pair(nx,ny));
        }
      }
    }
  }

  int ans = -1;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      for(int k=0; k<4; k++) {
        int x = i+dx[k];
        int y = j+dy[k];

        if(x>=0 && x<n && y>=0 && y<n) {
          if(g[i][j] != g[x][y]) {
            if(ans == -1 || ans > d[i][j] + d[x][y])
              ans = d[i][j] + d[x][y];  // ed: 거리가 가장 작은 값을 찾아서 ans에 저장한다
          }
        }
      }
    }
  }
  cout << ans << '\n';

  return 0;
}
