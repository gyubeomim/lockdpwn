#include <bits/stdc++.h>

using namespace std;

int R,C,K;
char region[6][6];
bool ck[6][6] = {0};

int roff[4] = {1,-1,0,0};
int coff[4] = {0,0,1,-1};

int ans=0;

void dfs(int r, int c, int dist){
	if(dist==K && r==0 && c==C-1){
		ans++;
		return;
	}

	for(int d=0; d<4; d++){
		int nr = r+roff[d];
		int nc = c+coff[d];

		if(nr<0||nr>=R || nc<0 || nc>=C) continue;
		if(region[nr][nc] == 'T') continue;
		if(ck[nr][nc]) continue;

		ck[nr][nc] = 1;
		dfs(nr, nc, dist+1);
		ck[nr][nc] = 0;
	}
}

int main() {
	cin >> R>>C>>K;

	for(int r=0;r<R;r++){
		for(int c=0; c<C;c++){
			cin >> region[r][c];
		}
	}

	ck[R-1][0] = 1;
	dfs(R-1, 0, 1);
	cout << ans << endl;
}	
