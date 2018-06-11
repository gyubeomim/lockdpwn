/*
 * #+DESCRIPTION:  백준 5427, 불 문제를 푼 정답 코드
 * #+CATEGORY:     BFS, Queue
 * #+LEVEL:        **
 * #+FROM:         http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220710219683&parentCategoryNo=271&categoryNo=303&viewDate=&isShowPopularPosts=false&from=postList
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int roff[4] = {-1,1,0,0};
const int coff[4] = {0,0,-1,1};

int main() {
  int T;
  cin >> T;

  for(int t=0; t<T; t++) {
    int W,H;
    char map[1000][1000];
    cin >> W >> H;
    bool visited[1000][1000] = {false};

    // Q는 상근이의 상태 큐, FQ는 불의 상태 큐
    queue<int> Q, FQ;
    for(int i=0; i<H; i++) {
      getchar();
      for(int j=0; j<W; j++) {
        map[i][j] = getchar();

        if(map[i][j] == '@') {
          visited[i][j] = true;
          Q.push(i*1000 + j);
        }
        else if(map[i][j] == '*')
          FQ.push(i*1000 + j);
      }
    }

    // success: 탈출 성공 여부
    bool success = false;
    int result = 0;
    // 상근이가 탈출했거나 더 갈 수 있는 곳이 없을 때까지 루프
    while(!Q.empty()) {
      result++;
      // 먼저 상근이가 이번 사건에 갈 수 있는 영역 확장
      int qSize=Q.size();
      for(int i=0; i<qSize; i++) {
        int r = Q.front()/1000;
        int c = Q.front()%1000;
        Q.pop();
        // 상근이는 불이 있는 곳으로 갈 수 없다
        if(map[r][c] == '*') continue;

        // 추가로 갈 수 있는 영역을 상태 큐에 넣는다
        for(int j=0; j<4; j++) {
          int nr = r + roff[j];
          int nc = c + coff[j];
          // 건물 밖으로 나온다: success
          if(nr<0 || nr>=H || nc<0 || nc>=W) {
            success=true;
            break;
          }
          // 인접한 영역을 큐에 push
          if(map[nr][nc] == '.' && !visited[nr][nc]) {
            visited[nr][nc] = true;
            Q.push(nr*1000 + nc);
          }
        }
      }
      if(success) break;
      // 그 다음, 불이 이번 시간에 추가로 번지는 곳들로 영역을 확장한다
      qSize = FQ.size();
      for(int i=0; i<qSize; i++) {
        int r = FQ.front()/1000;
        int c = FQ.front()%1000;
        FQ.pop();
        for(int j=0; j<4; j++) {
          int nr = r + roff[j];
          int nc = c + coff[j];
          if(nr<0 || nr>=H || nc<0 || nc>=W) continue;
          if(map[nr][nc] == '.') {
            map[nr][nc] = '*';
            FQ.push(nr*1000 + nc);
          }
        }
      }
    }
    // 결과 출력
    if(success) cout << result << endl;
    else puts("IMPOSSIBLE");
  }
  return 0;
}
