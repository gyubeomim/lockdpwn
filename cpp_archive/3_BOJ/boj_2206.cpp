/*
 * #+DESCRIPTION:  백준 2206, 벽 부수고 이동하기를 푼 정답 코드
 * #+CATEGORY:     BFS
 * #+LEVEL:        -
 * #+FROM:         http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220573411336&parentCategoryNo=271&categoryNo=303&viewDate=&isShowPopularPosts=false&from=postList
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

const int dx[4] = {-1,1,0,0};
const int dy[4] = {0,0,-1,1};

int main() {
  int N,M;
  cin >> N >> M;

  bool map[1000][1000];

  for(int i=0; i<N; i++) {
    for(int j=0; j<M; j++) {
      scanf("%1d", &map[i][j]);
    }
  }

  bool visited[2][1000][1000] = {false};
  visited[0][0][0]=true;

  queue<int> Q;
  Q.push(0);
  int result = 1;

  while(!Q.empty()) {
    int qSize = Q.size();
    bool reach = false;
    for(int i=0; i<qSize; i++) {
      /*
        매 상태는 crash, x, y 3개의 값의 해시값으로 나타낸다.
        crash는 벽을 하나 부쉈는지의 여부, false이면 아직 안 부숨
      */
      bool crash = Q.front() / (N*M);
      int x = Q.front() % (N*M) / M;
      int y = Q.front() % M;
      Q.pop();

      // 도착점에 온 경우, reach를 set하고 빠져나온다
      if(x == N-1 && y == M-1) {
        reach = true;
        break;
      }

      for(int d=0; d<4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        if(nx<0 || nx>=N || ny<0 || ny>=M) continue;
        if(visited[crash][nx][ny]) continue;
        // 다음 지점이 벽이고 아직 안 부쉈다면 부수고 간다
        if(map[nx][ny]) {
          if(crash) continue;
          visited[1][nx][ny] = true;
          Q.push(N*M + nx*M + ny);
        }
        // 벽이 아닌 경우
        else {
          visited[crash][nx][ny] = true;
          Q.push(crash*N*M + nx*M + ny);
        }
      }
    }
    if(reach) break;
    result++;
  }

  // 도착한 경우
  if(visited[0][N-1][M-1] || visited[1][N-1][M-1])
    cout << result << endl;
  // 도착하지 못한 경우
  else
    cout << "-1" << endl;

  return 0;
}
