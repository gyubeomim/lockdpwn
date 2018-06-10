/*
 * #+DESCRIPTION:  백준 2096, 내려가기 문제를 푼 정답코드
 * #+CATEGORY:     DP
 * #+LEVEL:        -
 * #+FROM:         http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220554100838&parentCategoryNo=271&categoryNo=303&viewDate=&isShowPopularPosts=false&from=postList
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
  int N;
  cin >> N;

  int tempMax[3]={0};
  int colMax[3]={0};
  int tempMin[3]={0};
  int colMin[3]={0};

  for(int i=0; i<N; i++) {
    for(int j=0; j<3; j++) {
      cin >> tempMax[j];
      tempMin[j] = tempMax[j];
      tempMax[j] += max(colMax[1], (j==1) ? max(colMax[0],colMax[2]):colMax[j]);
      tempMin[j] += min(colMin[1], (j==1) ? min(colMin[0],colMin[2]):colMin[j]);
    }
    memcpy(colMax, tempMax, sizeof(int)*3);  // DP 사용
    memcpy(colMin, tempMin, sizeof(int)*3);  // 메모라이제이션 대신 직전 값만을 저장하여 사용한
  }
  sort(colMax, colMax+3);
  sort(colMin, colMin+3);
  std::cout << colMax[2] << " " << colMin[0] << endl;

  return 0;
}
