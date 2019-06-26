

#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int v, chk[1001], gph[1001][1001];

void dfs(int now) {
  chk[now] = 1;

  for(int i=1; i<=v; i++) {
    if(!chk[i] && gph[now][i]) {
      dfs(i);
    }
  }
}

int main() {
  int T;
  cin >> T;

  while(T--) {
    cin >> v;

    int x;
    for(int i=1; i<=v; i++) {
      scanf("%d ", &x);
      gph[i][x] = gph[x][i] = 1;
    }

    int result = 0;

    for(int i=1; i<=v; i++) {
      if(!chk[i]) {
        dfs(i);
        result += 1;
      }
    }
    cout << result << '\n';
    memset(chk, 0, sizeof(chk));
    memset(gph, 0, sizeof(gph));
  }
  return 0;
}