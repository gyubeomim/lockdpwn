// @level:             2
// @category:          DP
// @description:       BOGGLE
#include <bits/stdc++.h>

using namespace std;

const int dr[8] = {-1,-1,-1,1,1,1,0,0};
const int dc[8] = {0,1,-1,0,1,-1,1,-1};

char board[5][5];
bool visited[5][5][10];
char word[10];
int length;

bool solution(int r, int c, int idx) {
  int ni = idx + 1;
  if(ni >= length) {
    return true;
  }

  for(int d=0; d<8; d++) {
    int nr = r + dr[d];
    int nc = c + dc[d];

    if( nr>=0 && nr<5 &&
        nc>=0 && nc<5 &&
        !visited[nr][nc][ni] &&
        (board[nr][nc] == word[ni]))
    {
      if(solution(nr, nc, ni))
      {
        return true;
      }
    }
  }

  visited[r][c][idx] = true;
  return false;
}

int main(int argc, char** argv) {
  int T;
  scanf("%d", &T);

  for(int t=0; t<T; t++) {
    for(int i=0; i<5; i++) {
      scanf("%s", board[i]);
    }

    int N;
    scanf("%d", &N);

    for(int i=0; i<N; i++) {
      scanf("%s", word);

      length = strlen(word);
      memset(visited, 0, sizeof(visited));

      bool is_found = false;
      for(int r=0; r<5; r++) {
        for(int c=0; c<5; c++) {
          if(board[r][c] == word[0] &&
             solution(r,c,0))
          {
            is_found = true;
          }
        }
      }

      if(is_found) {
        printf("%s YES\n", word);
      }
      else {
        printf("%s NO\n", word);
      }
    }
  }

  return 0;
}
