/*
 * #+DESCRIPTION:  백준 2667, 단지 번호붙이기 문제를 푼 정답코드, DFS를 사용해서 문제를 풀었다
 * #+CATEGORY:     GRAPH, DFS
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

int a[30][30];
int group[30][30];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
int n;
int ans[25*25];

void dfs (int x, int y, int cnt ) {
  group[x][y] = cnt;

  for(int k=0; k<4; k++) {
    int nx = x + dx[k];
    int ny = y + dy[k];

    if(nx>=0 && nx <n && ny>=0 && ny<n) {
      if(a[nx][ny] == 1 && group[nx][ny] == 0) {
        dfs(nx,ny,cnt);
      }
    }
  }
}

int main() {
  cin >> n;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++)
      scanf("%1d", &a[i][j]);
  }

  int cnt=0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(a[i][j] == 1 && group[i][j] == 0)
        dfs(i, j, ++cnt); // ed: DFS 사용
    }
  }

  cout << cnt << '\n';

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      ans[group[i][j]] += 1;
    }
  }

  sort(ans+1, ans+cnt+1);

  for(int i=1; i<=cnt; i++) {
    cout << ans[i] << '\n';
  }

  return 0;
}
