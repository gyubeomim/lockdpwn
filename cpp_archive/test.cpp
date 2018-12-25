#include <cstdio>
#include <queue>

using namespace std;

const int roff[4] = {-1,1,0,0};
const int coff[4] = {0,0,-1,1};

int main() {
    int N,M;
    scanf("%d %d", &N, &M);
    bool map[100][100];

    for(int i=0; i<N; i++)
        for (int j=0; j<M; j++)
            scanf("%1d", &map[i][j]);

    // visited 배열: false일 때만 새로 이동한다
    bool visited[100][100] = {0};
    visited[0][0] = true;

    // 사용할 큐. 이 때 각 상태를 행*100 + 열의 해시값으로 사용한다
    queue<int> Q;
    Q.push(0);

    // 이동횟수
    int result = 1;

    while(true) {
        int qSize = Q.size();
        for(int i=0 ; i<qSize ; i++){
            int r = Q.front()/100;
            int c = Q.front()%100;
            Q.pop();

            if(r==N-1 && c==M-1){
                printf("%d\n", result);
                return 0;
            }

            for(int d=0; d<4; d++){
                int nr = r + roff[d];
                int nc = c + coff[d];

                if(nr<0 || nr>=N || nc<0 || nc>=M) continue;
                if(!map[nr][nc]) continue;
                if(visited[nr][nc]) continue;

                visited[nr][nc] = true;
                Q.push(nr*100 + nc);
            }
        }
        result++;
    }
}
