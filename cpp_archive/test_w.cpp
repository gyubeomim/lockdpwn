#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int N, num;
int map[101][101], visited[101][101] = {0};

bool chk(int x,int y){
	return 0<=x && x<N && 0<=y && y<N;
}

void dfs(int x, int y, int num) {
  visited[x][y] = true;
  map[x][y] = num;

  for (int d = 0; d < 4; d++) {
    int nx = x + dx[d];
    int ny = y + dy[d];
    if (chk(nx, ny) && map[nx][ny] && !visited[nx][ny])
      dfs(nx, ny, num);
  }
}

int bfs(int num) {
	queue<pair<int,int>> Q;
	memset(visited,0,sizeof(visited));

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(map[i][j]==num){
				visited[i][j]=1;
				Q.push({i,j});
			}
		}
	}

	int result = 0;
	while(!Q.empty()) {
		int qsize = Q.size();
		while(qsize--){
			int x=Q.front().first;
			int y=Q.front().second;
			Q.pop();

			for(int d=0;d<=4;d++){
				int nx=x+dx[d];
				int ny=y+dy[d];

				if(!chk(nx,ny)) continue;
				if(map[nx][ny] !=0 && map[nx][ny]!=num) return result;
				if(map[nx][ny]==0&&!visited[nx][ny]){
					visited[nx][ny]=1;
					Q.push({nx,ny});
				}
			}
		}
		result+=1;
	}
}

int main() {
  cin >> N;
  if (N == 0) return 0;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> map[i][j];
      // cout << "map[" << i <<"]["<<j<<"]: " << map[i][j]<<endl;
    }
  }

	for(int i=0;i<N;i++) {
		for(int j=0;j<N;j++){
			if(map[i][j] && !visited[i][j])
			dfs(i,j,++num);
		}
	}

	int min_dist = 9999;

	for(int i=1;i<=num;i++){
		min_dist = std::min(min_dist,bfs(i));
	}
	cout << min_dist << '\n';

  return 0;
}
