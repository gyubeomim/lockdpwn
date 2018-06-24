/*
 * #+DESCRIPTION:  백준 2110, 공유기 설치 문제를 푼 정답 코드
 * #+CATEGORY:     Greedy, Binary Search
 * #+LEVEL:        -
 * #+FROM:         http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220444432628&parentCategoryNo=271&categoryNo=302&viewDate=&isShowPopularPosts=false&from=postList
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <algorithm>

using namespace std;

int N, C, x[200000], limit;

// current번째 집부터 공유기를 remian개 설치할 수 있는지 확인하는 함수
bool possible(int current, int remain) {
  // 기저사례: 더 설치할 공유기가 없는 경우
  if(remain == 0) return true;

  for(int i=current+1; i<N; i++) {
    if(x[i]-x[current] >= limit)
      return possible(i, remain-1);
  }

  return false;
}

int main(int argc, char **argv) {
  cin >> N >> C;
  for(int i=0; i<N; i++) {
    cin >> *(x+i);
  }
  sort(x, x+N);

  // 이분 탐색: upper는 불가능, lower는 가능한 거리
  int upper = x[N-1]+1;
  int lower = 1;
  while(lower+1 < upper) {
    limit = (upper+lower)/2;
    if(possible(0,C-1))
      lower = limit;
    else
      upper = limit;
  }
  cout << lower << endl;

  return 0;
}
