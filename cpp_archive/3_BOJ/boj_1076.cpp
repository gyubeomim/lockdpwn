/*
  c++ ==> 백준 1076, 저항 문제를 푼 코드

          전자 제품에는 저항이 들어간다. 저항은 색 3개를 이용해서 그 저항이 몇 옴인지 나타낸다.
          처음 색 2개는 저항의 값이고, 마지막 색은 곱해야 하는 값이다.
          첫째 줄에 입력을 주어진 저항의 저항값을 출력한다.

          Input  : yello violet red
          Output : 4700
*/
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(int argc, char **argv) {
  map<string, int> d = {
    {"black", 0}, {"brown", 1}, {"red", 2},
    {"orange", 3}, {"yellow", 4}, {"green", 5},
    {"blue", 6}, {"violet", 7}, {"grey", 8},
    {"white", 9}
  };

  string a,b,c;
  cin >> a >> b >> c;

  // ed: yellow violet red 입력을 처리하는 코드
  long long ans = (long long)(d[a]*10 + d[b]);
  for (int k=0; k<d[c]; k++) {
    ans *= 10LL;
  }

  cout << ans << '\n';
  return 0;
}
