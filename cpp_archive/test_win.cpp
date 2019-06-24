

#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>

using namespace std;

int n, e, chk[1001], gph[1001][1001];

void dfs(int now) {
  chk[now] = 1;
  for(int i=1; i<=n; i++) {
    if (!chk[i] && gph[now][i]) {
      dfs(i);
    }
  }
}

int main() {
  cin >> n >> e;

  for(int i=0; i<e; i++) {
    int x,y;
    cin >> x >> y;
    gph[x][y] = gph[y][x] = 1;
  }

  int count = 0;
  for(int i=1; i<=n;i++){
    if(!chk[i]) {
      dfs(i);
      count += 1;
    }
  }

  cout << count << '\n';

  return 0;
}