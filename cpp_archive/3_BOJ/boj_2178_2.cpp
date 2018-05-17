/*
  c++ ==> 백준 2178, 미로 탐색을 푼 정답코드


  code from [http://gnujoow.github.io/boj/2016/10/15/BOJ6-2178/]
*/
#include <iostream>
#include <queue>
#include <cstdio>

using namespace std;

int N,M;
int map[100][100] = {0};
const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,1,-1};

void bfs(int x,int y) {
  queue<pair<int,int>> q;
  q.push(make_pair(x, y));

  while(!q.empty()) {
    x = q.front().first;
    y = q.front().second;
    q.pop();

    for(int d=0; d<4; d++) {
      int nx = x + dx[d];
      int ny = y + dy[d];

      if(nx < 0 || nx > N-1 || ny < 0 || ny > M-1) continue;
      if(map[nx][ny]==1){
        q.push(make_pair(nx, ny));
        map[nx][ny] = map[x][y]+1;
      }
    }
  }
}

int main() {
  cin >> N >> M;
  for(int i=0; i<N; i++) {
    for(int j=0; j<M; j++) {
      scanf("%1d", &map[i][j]);
    }
  }

  map[0][0]=2;
  bfs(0,0);
  cout << map[N-1][M-1]-1 << endl;

  return 0;
}

