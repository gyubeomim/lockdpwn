

#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

int v, e, x, y, chk[1001], gph[1001][1001];

void bfs(int now) {
  queue<int> que;
  que.push(now);
  chk[now] = 1;

  while(!que.empty()) {
    int now = que.front();
    que.pop();

    for (int i = 1; i <= e; i++) {
      if(!chk[i] && gph[now][i]) {
        que.push(i);
        chk[i] = 1;

      }
    }

    if (que.size() >= 2) {
      cout << "YES\n";
      return;
    }
  }
  cout << "NO\n";
}

int main() {
  int T,t;
  cin >> T;

  t = 1;

  while(t <= T) {
    cin >> v >> e;

    for(int i=0; i<e; i++) {
      cin >> x >> y;
      gph[x][y] = gph[y][x] = 1;
    }

    bfs(1);

    cout << "-------------------\n";
    t += 1;
  }


  return 0;
}