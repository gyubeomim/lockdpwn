/*
  c++ ==> 백준 1018, 체스판 문제를 푼 정답 코드
          Brute force 방식으로 모든 경우의수를 돌면서 정답을 계산하는 방식

  code from [http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220613894923&parentCategoryNo=271&categoryNo=303&viewDate=&isShowPopularPosts=false&from=postList]
*/
#include <iostream>
#include <cstdio>
using namespace std;

int main() {
  int M,N;
  char map[50][50];
  cin >> N >> M;
  for(int i=0; i<N; i++) {
    getchar(); // '\n' 문자를 처리하는 코드
    for(int j=0; j<M; j++) {
      map[i][j] = getchar();
    }
  }

  // 기본 결과는 아주 큰 값으로 시작. 다만 64는 절대 나올 수 없다
  int result = 64;
  for(int i=0; i<=N-8; i++) {
    for(int j=0; j<=M-8; j++) {
      int cnt=0;
      // 모든 8*8 영역을 체크해서 체스판과 다른 칸 개수를 센다
      for(int r=0; r<8; r++)
        for(int c=0; c<8; c++)
          cnt += (r%2==c%2 ? 'W':'B')==map[i+r][j+c];
      // 원래 체스판
      result = min(result, cnt);
      // 체스판을 90도 회전한 것과도 비교
      result = min(result, 64-cnt);
    }
  }
  cout << result << endl;

  return 0;
}
