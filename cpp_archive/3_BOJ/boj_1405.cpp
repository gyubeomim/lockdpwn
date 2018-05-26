/*
  c++ ==> 백준 1405, 미친 로봇 문제를 푼 정답 코드
          DFS를 사용해서 풀었다


  code from [http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220620727135&parentCategoryNo=271&categoryNo=303&viewDate=&isShowPopularPosts=false&from=postList]
*/
#include <iostream>
#include <cstdio>
using namespace std;

const int dx[4] = {0,0,1,-1};
const int dy[4] = {1,-1,0,0};

double P[4]={0};
int visited[29][29]={0};

// 현재 x행, c열에 있고 limit번 더 이동할 때 앞으로 단순경로일 확률
double crazyRobot(int x, int y, int limit) {
  // 기저 사례: 당장 탐색을 멈추므로 항상 단순하다
  if(limit==0) return 1.0;

  visited[x][y]=true;
  double result = 0;
  // DFS로 다른 방향들을 탐색하여 결과를 구한다
  for(int d=0; d<4; d++) {
    int nx = x + dx[d];
    int ny = x + dy[d];
    if(visited[nx][ny]) continue;
    // 해당 방향으로 이동할 확률을 곱해서 결과에 더한다
    result += P[d] * crazyRobot(nx,ny,limit-1);
  }

  visited[x][y]=false;
  return result;
}

int main() {
  int N;
  cin >> N;

  for(int i=0; i<4; i++) {
    int p;
    cin >> p;
    P[i] = p/100.0;
  }
  // N이 최대 14이므로 0~28까지의 행,열 번호를 쓰며 중앙은 14이다
  cout << crazyRobot(14, 14, N) << endl;
  return 0;
}
