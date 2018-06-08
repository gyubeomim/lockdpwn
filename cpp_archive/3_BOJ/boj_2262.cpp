/*
 * description:
 *  백준 2262, 토너먼트 만들기 문제를 푼 정답코드
 *             DP를 사용해서 풀었다
 *
 * author: Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAX = 256;
const int INF = 1000000000;

int N, R[MAX], minR[MAX][MAX], dp[MAX][MAX];

int minRankDiff(int start, int end) {
  int &ret = dp[start][end];
  if(ret != -1) return ret;
  if(start == end) return ret = 0;

  ret = INF;
  for(int m=start; m<end; m++)
    ret = min(ret, abs(minR[start][m] - minR[m+1][end]) + minRankDiff(start,m) + minRankDiff(m+1,end));
  return ret;
}

int main() {
  cin >> N;
  for(int i=0; i<N; i++)
    cin >> *(R+i);

  for(int i=0; i<N; i++) {
    for(int j=i; j<N; j++) {
      minR[i][j] = R[i];
      for(int k=i+1; k<=j; k++)
        minR[i][j] = min(minR[i][j], R[k]);
    }
  }
  memset(dp, -1, sizeof(dp));
  printf("%d\n", minRankDiff(0, N-1));

  return 0;
}
