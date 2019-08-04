/*
 * #+DESCRIPTION:  백준 2262, 토너먼트 만들기 문제를 푼 정답코드
 * #+CATEGORY:     DP
 * #+LEVEL:        -
 * #+FROM:         -
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAX = 256;
const int INF = 1000000000;

// R: 랭킹
// minR[i][j]: 구간 [i,j]의 가장 높은 랭킹(즉, 가장 작은 값)
int N, R[MAX], minR[MAX][MAX], dp[MAX][MAX];

int minRankDiff(int start, int end) {
  int &ret = dp[start][end];
  if(ret != -1) return ret;
  // base case: 구간 길이 1
  if(start == end) return ret = 0;

  ret = INF;
  // m을 순회하며 현재 구간을 m을 기준으로 두 구간으로 나눠서 부분 문제를 푼다.
  // 결과는 이 중에서 가장 작은 값
  for(int m=start; m<end; m++)
    ret = min(ret, abs(minR[start][m] - minR[m+1][end]) + minRankDiff(start,m) + minRankDiff(m+1,end));
  return ret;
}

int main() {
  cin >> N;
  for(int i=0; i<N; i++)
    cin >> *(R+i);

  // 전처리: 3중 for문으로 미리 minR 배열의 값을 구해 놓는다
  for(int i=0; i<N; i++) {
    for(int j=i; j<N; j++) {
      minR[i][j] = R[i];
      for(int k=i+1; k<=j; k++)
        minR[i][j] = min(minR[i][j], R[k]);
    }
  }

  // dp로 문제 풀기
  memset(dp, -1, sizeof(dp));
  printf("%d\n", minRankDiff(0, N-1));

  return 0;
}
