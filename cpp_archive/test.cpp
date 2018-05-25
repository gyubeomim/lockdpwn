#include <iostream>
#include <cstdio>
using namespace std;

int main() {
  int M,N;
  cin >> N >> M;

  char map[50][50];
  for(int i=0; i<N; i++) {
    getchar();
    for(int j=0; j<M; j++) {
      map[i][j] = getchar();
    }
  }

  int result = 64;
  for(int i=0; i<=N-8; i++) {
    for(int j=0; j<=M-8; j++) {
      int cnt = 0;
      for(int r=0; r<8; r++)
        for(int c=0; c<8; c++)
          cnt += (r%2==c%2 ? 'W':'B') == map[i+r][j+c];

      result = min(result, cnt);
      result = min(result, 64-cnt);
    }
  }
  cout << result << endl;

  return 0;
}
