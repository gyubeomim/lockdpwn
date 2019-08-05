/*
 * #+DESCRIPTION:  백준 5893, 17배 문제를 푼 정답코드
 * #+CATEGORY:     Binary
 * #+LEVEL:        **
 * #+FROM:         http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220693068520&parentCategoryNo=271&categoryNo=303&viewDate=&isShowPopularPosts=false&from=postList
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
  // B=N 일 때, 17N = B + 16B(=A) 이므로 A+B의 연산을 수행하면 된다
  string A,B;
  cin >> B;

  // 계산의 편의를 위해 제일 왼쪽 자리를 LSB로 맞춘다
  reverse(B.begin(), B.end());
  A = "0000" + B;

  bool carry = false;
  int i;
  // B의 length만큼 계산한다
  for(i=0; i<B.size(); i++) {
    int val = A[i]-'0' + B[i]-'0' + carry;
    if(val >= 2) {
      val -= 2;
      carry = true;
    }
    else carry = false;
    A[i] = val + '0';
  }
  // B의 범위를 넘어가는 A의 4자리 계산
  for(; i<A.size(); i++) {
    int val = A[i]-'0' + carry;
    if(val == 2) {
      val = 0;
      carry = true;
    }
    else carry = false;
    A[i] = val + '0';
  }

  if(carry) A.push_back('1');
  reverse(A.begin(), A.end());
  cout << A << endl;

  return 0;

}
