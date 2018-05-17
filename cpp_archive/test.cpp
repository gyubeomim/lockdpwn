/*
  c++ ==> 백준 2716, 원숭이 매달기 문제를 푼 정답코드


  code from [http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220444375611&parentCategoryNo=271&categoryNo=302&viewDate=&isShowPopularPosts=false&from=postList]
*/
#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

int main() {
  int N;
  cin >> N;
  cin.ignore();

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
