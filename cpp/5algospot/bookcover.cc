// @level:             2
// @category:          Search
// @description:       BOARDCOVER
#include <bits/stdc++.h>

using namespace std;

int blocks[4][3][2] {
  {{0,0}, {1,0}, {0,1}},
  {{0,0}, {0,1}, {1,1}},
  {{0,0}, {1,0}, {1,1}},
  {{0,0}, {1,0}, {1,-1}}
};
int R,C;
int board[20][20];

bool check(int y, int x, int type, int delta) {
  bool ok = true;
  for(int i=0; i<3; i++) {
    int ny = y + blocks[type][i][0];
    int nx = x + blocks[type][i][1];

    if(ny<0 || ny>=R || nx<0 || nx>=C) {
      ok = false;
    }
    else if((board[ny][nx] += delta) > 1) {
      ok = false;
    }
  }
  return ok;
}

int solution() {
  int y=-1, x=-1;

  for(int r=0; r<R; r++) {
    for(int c=0; c<C; c++) {
      if(board[r][c] == 0) {
        y=r;
        x=c;
        break;
      }
    }
    if(y!=-1) {
      break;
    }
  }

  if(y==-1) {
    return 1;
  }

  int count = 0;
  for(int type=0; type<4; type++) {
    if(check(y,x,type,1)) {
      count += solution();
    }

    check(y,x,type,-1);
  }
  return count;
}

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int T;
  cin >> T;

  char text[20];
  while(T--) {
    cin >> R >> C;
    for(int r=0; r<R; r++) {
      cin >> text;
      for(int c=0; c<C; c++) {
        board[r][c] = (text[c] == '#') ? 1 : 0;
      }
    }

    cout << solution() << endl;
  }

  return 0;
}
