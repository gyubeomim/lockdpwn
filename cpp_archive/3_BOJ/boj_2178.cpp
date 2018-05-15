/*
  c++ ==> 백준 2178, 미로 탐색 문제를 BFS로 푼 코드

  code from [http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220574993422&parentCategoryNo=271&categoryNo=302&viewDate=&isShowPopularPosts=false&from=postList]
*/
#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

const int roff[4] = {-1, 1, 0, 0};
const int coff[4] = {0, 0, -1, 1};

int main(int argc, char **argv) {
  int N,M;
  cin >> N >> M;
  bool map[100][100];

  for(int i=0; i<N; i++) {
    for(int j=0; j<M; j++) {
      scanf("%1d", &map[i][j]);
    }
  }

  // visited 배열: false일 때만 새로 이동한다
  bool visited[100][100] = {0};
  visited[0][0] = true;

  // 사용할 큐. 이때 각 상태를 "행*100+열"의 해시값으로 사용한다
  queue<int> Q;
  Q.push(0);

  // 이동횟수
  int result = 1;

  /*
    원래 while문은 큐가 비어있지 않은 동안만 돌려야 하지만
    이 문제의 경우 항상 도착 가능한 경우만 주어지므로 그럴 필요가 없다.
    만약 도착하지 전에 큐가 비게 된다면, 도착할 수 없는 경우이다
   */
  while(true) {
    // 현재 큐의 원소 개수만큼 안쪽 for문을 실행한다
    int qSize = Q.size();
    for(int i=0; i<qSize; i++) {
      // 해시값으로부터 현재 위치의 행, 열 번호를 가져옴
      int r = Q.front()/100;
      int c = Q.front()%100;
      Q.pop();
      // 도착한 경우, 이동 횟수를 출력하고 프로그램 종료
      if(r == N-1 && c == M-1) {
        cout << result;
        return 0;
      }

      /*
        각 방향마다 일일히 코딩할 수도 있지만
        offset 배열로 각 방향마다의 행, 열 이동 거리를 계산하면
        for문을 4번 돌려서 코딩하는 것도 가능하다
       */
      for(int d=0; d<4; d++) {
        // 이동한 후의 위치
        int nr = r + roff[d];
        int nc = c + coff[d];
        // 미로 바깥으로는 이동 불가능
        if(nr<0 || nr>=N || nc<0 || nc>=M) continue;
        // 벽이면 방문 불가능
        if(!map[nr][nc]) continue;

        // 방문한 것으로 갱신하고, 큐에 새로 넣어 다음에 방문
        if(visited[nr][nc]) continue;

        visited[nr][nc] = true;
        Q.push(nr*100 + nc);
      }
    }

    // 안쪽 for문이 끝날 때마다 이동 횟수 증가
    result++;
  }
  return 0;
}
