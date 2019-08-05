/*
 * #+DESCRIPTION:  백준 2281, 데스노트 문제를 푼 정답 코드
 * #+CATEGORY:     DP
 * #+LEVEL:        -
 * #+FROM:         http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220547614387&parentCategoryNo=271&categoryNo=303&viewDate=&isShowPopularPosts=false&from=postList
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
int N, M, len[1000], cache[1000][1000];

/*
현재 col번째 열부터 쓸 것이고 cur개의 단어를 이미 썼을 때
남은 단어를 모두 쓰고 얻을 수 있는 공백 제곱의 합의 최소값을 구하는 함수
*/
int minSquareSum(int col, int cur) {
  // 기저사례: 모든 단어를 다 씀
  if(cur == N)
    return 0;
  // 해당 열을 꽉 채워 쓰거나 한 칸만 남은 경우
  if(col >= M)
    return minSquareSum(len[cur]+1, cur+1) + (col==M?1:0);

  int &ret = cache[col][cur];
  if(ret != -1)
    return ret;

  // 다음 줄로 옮겨 쓰면서 남은 여백의 칸수 제곱을 더한다
  ret = minSquareSum(len[cur]+1, cur+1) + (M-col+1)*(M-col+1);

  // 해당 줄에서 이어서 쓸 수 있는 경우
  if(col+len[cur] <= M)
    ret = min(ret, minSquareSum(col+len[cur]+1, cur+1));

  return ret;
}


int main() {
  cin >> N >> M;
  for(int i=0; i<N; i++) {
    scanf("%d", len+i);
  }

  memset(cache, -1, sizeof(cache));
  cout << minSquareSum(len[0]+1, 1) << endl;

  return 0;
}
