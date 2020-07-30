// @date:              2020.07.30.Thu
// @level:             1
// @category:          BFS
// @description:       2178. 미로 탐색
#include <bits/stdc++.h>

using namespace std;

const int roff[4] = {-1,1,0,0};
const int coff[4] = {0,0,-1,1};

int main(int argc, char** argv) {
  int N,M;
  cin >> N >> M;

  int map[100][100];
  int visited[100][100];
  memset(map, 0, sizeof(map));
  memset(visited, 0, sizeof(visited));

  for(int r=0; r<N; r++) {
    for( int c=0; c<M; c++) {
      scanf("%1d", &map[r][c]);
    }
  }

  visited[0][0] = 1;

  queue<int> Q;
  Q.push(0);

  int result = 1;

  while(true) {
    int q_size = Q.size();

    for(int i=0; i<q_size; i++) {
      int r = Q.front()/100;
      int c = Q.front()%100;
      Q.pop();

      if(r == N-1 && c == M-1) {
        cout << result << '\n';
        return 0;
      }

      for(int d=0; d<4; d++) {
        int nr = r + roff[d];
        int nc = c + coff[d];

        if(nr < 0 || nr >= N || nc < 0 || nc >= M) {
          continue;
        }
        if(map[nr][nc] == 0) {
          continue;
        }
        if(visited[nr][nc]) {
          continue;
        }

        visited[nr][nc] = 1;
        Q.push(nr*100 + nc);
      }
    }
    result += 1;
  }

  return 0;
}
