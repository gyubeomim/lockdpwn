/*
 * #+DESCRIPTION:  백준 1700, 멀티탭 스케쥴링 문제를 푼 정답코드
 * #+CATEGORY:     greedy
 * #+LEVEL:        **
 * #+FROM:         http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220735252997&parentCategoryNo=271&categoryNo=303&viewDate=&isShowPopularPosts=false&from=postList
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
using namespace std;

int main() {
  // use[i]: i 번째 구에 꽂혀있는 전기용품의 번호
  // plan[i]: i 번째로 사용할 전기용품의 번호
  int N,K, use[100]={0}, plan[100];
  cin >> N >> K;
  for(int i=0; i<K; i++)
    cin >> *(plan+i);

  int result=0;
  for(int i=0; i<K; i++) {
    // 먼저 해당 전기용품이 이미 꽂혀 있는지 확인
    bool inUse = false;

    for(int j=0; j<N; j++)
      if(plan[i] == use[j]) {
        inUse = true;
        break;
      }
    // 이미 꽂혀 있다면 아무것도 뽑을 필요 없음
    if(inUse) continue;

    // 아직 비어 있는 구멍이 있는지 확인
    inUse = false;
    for(int j=0; j<N; j++)
      if(use[j] == 0) {
        // 비어 있는 구멍이 있다면 거기에 꽂음
        use[j] = plan[i];
        inUse = true;
        break;
      }
    // 비어 있는 구멍이 있다면 아무것도 뽑을 필요 없음
    if(inUse) continue;

    // 가장 나중에 다시 사용될 전기용품을 찾음
    int swap, val = -1;
    for(int j=0; j<N; j++) {
      int term = 0;
      for(int k=i+1; k<K && use[j]!=plan[k]; k++) term++;

      if(term > val) {
        swap = j;
        val = term;
      }
    }
    // 풀러그를 뽑는 횟수 1 증가
    result++;
    // 해당 구멍에 꽂혀 있는 전기용품을 바꿈
    use[swap] = plan[i];
  }
  cout << result << endl;
  return 0;
}
