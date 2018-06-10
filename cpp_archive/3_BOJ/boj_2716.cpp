/*
 * #+DESCRIPTION:  백준 2716, 원숭이 매달기 문제를 푼 정답코드
 * #+CATEGORY:
 * #+LEVEL:        -
 * #+FROM:         http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220444375611&parentCategoryNo=271&categoryNo=302&viewDate=&isShowPopularPosts=false&from=postList
 * #+DATE:         2018-06-10-일
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

int main() {
  int N;
  cin >> N;
  cin.ignore();  // ed: 이 코드가 빠지만 cin이 '\n'을 읽지 않아서 아래 코드가 꼬인다

  for(int i=0; i<N; i++) {
    char S[151], c;
    int len = 0;

    while((c=getchar()) != '\n') {
      S[len++] = c;
    }

    int level=0, maxlevel=0;

    for(int j=0; j<len; j++) {
      if(S[j] == '[') {
        level++;
        if(level > maxlevel)  maxlevel = level;
      }
       else
         level--;
    }
    int ans = pow(2,maxlevel);
    cout << ans << endl;
  }

  return 0;
}
