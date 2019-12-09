/*
 * #+DESCRIPTION:  백준 1629, 곱셈 문제를 푼 정답 코드
 * #+CATEGORY:
 * #+LEVEL:        -
 * #+FROM:         http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220583413569&parentCategoryNo=271&categoryNo=302&viewDate=&isShowPopularPosts=false&from=postList
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <cstdio>

using namespace std;

int A,B,C;

// 0이 아닌 n에 대해 n^k를 구하는 재귀함수
int power(int n, int k) {
  // 기저 사례: n^0 = 1
  if(k==0) return 1;

  int temp = power(n, k/2);
  int result = 1LL * temp * temp % C;

  // 홀수이면 n을 한 번 더 곱해준다
  if(k%2) result = 1LL * result * n % C;

  return result;
}

int main(int argc, char **argv) {
  scanf("%d %d %d", &A, &B, &C);
  printf("%d\n", power(A,B));

  return 0;
}
