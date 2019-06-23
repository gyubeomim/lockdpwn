

#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

int n, e, v, chk[1001], gph[1001][1001];

void dfs(int now) { 
  chk[now] = 1;
  cout << now << " ";

  for(int i=1; i<=n; i++) { 
    if(!chk[i] && gph[now][i]) {
      dfs(i);
    }
  }
}


void bfs(int now){ 
  queue<int> que;
  que.push(now);
  chk[now] = 1;

  while(!que.empty()) {
    int now = que.front();
    que.pop();
    cout << now << " ";

    for(int i=1; i<=n; i++) {
      if(!chk[i] && gph[now][i]) {
        que.push(i);
        chk[i] = 1;
      }
    }
  }
}

int main() {
  cin >> n >> e >> v;

  for(int i=0; i<e; i++) {
    int x,y;
    cin >> x >> y;
    gph[x][y] = gph[y][x] = 1;
  }

  dfs(v);
  cout << '\n';
  memset(chk, 0, sizeof(chk));
  bfs(v);

  return 0;
}