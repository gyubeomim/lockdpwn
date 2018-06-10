/*
 * #+DESCRIPTION:  백준 2096, 내려가기 문제를 푼 정답 코드
 * #+CATEGORY:
 * #+LEVEL:        -
 * #+FROM:         https://github.com/simjaemun2/BaekJoon/blob/7e1e8fa7ca3f040ecabc41ea9954532166dc81ca/BOJ2096/BOJ2096.cpp
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int input[3];
int cacheMax[3];
int cacheMin[3];
int N;

int main() {
  cin >> N;

  for(int i=0; i<N; i++) {
    cin >> input[0] >> input[1] >> input[2];
    int t0 = cacheMax[0];
    int t1 = cacheMax[1];
    int t2 = cacheMax[2];

    cacheMax[0] = max(t0,t1) + input[0];
    cacheMax[1] = max({t0,t1,t2}) + input[1];
    cacheMax[2] = max(t1,t2) + input[2];

    t0 = cacheMin[0];
    t1 = cacheMin[1];
    t2 = cacheMin[2];

    cacheMin[0] = min(t0,t1) + input[0];
    cacheMin[1] = min({t0,t1,t2}) + input[1];
    cacheMin[2] = min(t1,t2) + input[2];
  }
  cout << max({cacheMax[0],cacheMax[1],cacheMax[2]}) << " " << min({cacheMin[0],cacheMin[1],cacheMin[2]}) << endl;

  return 0;
}
