

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

const int roff[4] = {-1, 1, 0 ,0};
const int coff[4] = {0,0,-1,1};
bool map[25][25];
bool visited[25][25] = {0};
queue<int> Q;
vector<int> v;

int bfs(int r, int c) {
  if(map[r][c] == 1) {
    Q.push(r*25 + c);
  }

  while(!Q.empty()){
    for(int d=0; d<4; d++) {
    int nr = r + roff[d];
    int nc = c + coff[d];

    }
  } 

}

int main() {
  int N;
  cin >> N;

  for(int i=0; i<N; i++){
    for(int j=0;j<N;j++){
      scanf("%1d", &map[i][j]);
    }
  }


  int num = 0;
  for(int r=0;r<N;r++){
    for(int c=0;c<N;c++){
      num = bfs(r,c);
      if(num != 0) {
        v.push_back(num);
      }
    }
  }

  std::sort(v.begin(), v.end());
  for(auto it : v) {
    cout << it << '\n';
  }

  return 0;
}