

#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;

const int roff[4] = {-1, 1, 0, 0};
const int coff[4] = {0, 0, -1, 1};
int N,M;
int map[1000][1000];
bool visited[1000][1000] = {0};
queue<int> Q;

int main() {
	cin >> N >> M;
	if(N==0 && M==0) return 0;

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			// cout << "map[" << i <<"]["<<j<<"]: " << map[i][j]<<endl;
			if(map[i][j]==1) {
				Q.push(1000*i+j);
				visited[i][j] = true;
				// cout << "visited[" << i << "]["<< j << "]: " << visited[i][j] << endl;
			}
		}
	}

	int result = 0;

	while(!Q.empty()) {
		int qSize = Q.size();
		for(int i=0; i<qSize;i++) {
			int r=Q.front()/1000;
			int c=Q.front()%1000;
			Q.pop();

			for(int d=0; d<4; d++) {
				int nr=r+roff[d];
				int nc=c+coff[d];

				if (nr < 0 || nr >= M || nc < 0 || nc >= N) continue;
				if (map[nr][nc]==-1) continue;
				if (visited[nr][nc]) continue;

				visited[nr][nc] = true;
				map[nr][nc] = 1;
				Q.push(1000 * nr + nc);
			}
		}
		result += 1;
	}

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if(map[i][j]==0) {	
				cout << -1 << '\n';
				return 0;
			}
		}
	}
	cout << result-1 << '\n';

	return 0;
}
