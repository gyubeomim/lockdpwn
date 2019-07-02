

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

const int roff[9] = {0, -1, 1, 0, 0, -1, -1, 1, 1};
const int coff[9] = {0, 0, 0, -1, 1, -1, 1, -1, 1};
int N,M;
bool map[50][50];
bool visited[50][50] = {0};
queue<int> Q;

bool bfs(int r, int c) {
  if (visited[r][c]) return false;

  if (map[r][c] == 1) {
    // cout << "r: " << r<<", c: " << c <<endl;
    Q.push(50 * r + c);
  } 
  else
    return false;

  while (!Q.empty()) {
    int qSize = Q.size();
    for (int i = 0; i < qSize; i++) {
      int r = Q.front() / 50;
      int c = Q.front() % 50;
      Q.pop();

      for (int d = 0; d < 9; d++) {
        int nr = r + roff[d];
        int nc = c + coff[d];

        if (nr < 0 || nr >= M || nc < 0 || nc >= N) continue;
        if (!map[nr][nc]) continue;
        if (visited[nr][nc]) continue;

        visited[nr][nc] = true;
        Q.push(50 * nr + nc);
      }
    }
  }
  return true;
}

int main() {
  while (true) {
    cin >> N >> M;
    if(N==0&&M==0) return 0;

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        cin >> map[i][j];
        // cout << "map[" << i <<"]["<<j<<"]: " << map[i][j]<<endl;
      }
    }
    int count = 0;
    // cout << "N: " << N << ", M: " << M << endl;
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        if (bfs(i, j)) {
          // cout << "i: " << i << ", j: " << j << endl;
          count += 1;
        }
      }
    }
    cout << count << '\n';
    memset(map,0,sizeof(map));
    memset(visited,0,sizeof(visited));
  }

  return 0;
}