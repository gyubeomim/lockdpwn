/*
  c++ ==> 백준 5052, 전화번호 목록 문제를 푼 정답코드

          substr() 함수를 사용해서 간단하게 풀었다. 이 방식이 조금 더 직관적인듯

  code from [https://fatc.club/2017/03/01/889]
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int N;
  vector<string> v;
  int T;

  cin >> T;
  while(T--) {
    string tmp;
    cin >> N;
    v = vector<string>(N);

    for(int i=0; i<N; ++i) {
      cin >> v[i];
    }
    sort(v.begin(), v.end());
    bool ans = true;

    for(int i=1; i<N; i++) {
      string& a = v[i-1];
      string& b = v[i];

      if(a.size() > b.size()) continue;
      if(a == b.substr(0, a.size())) {
        ans = false;
        break;
      }
    }
    puts(ans ? "YES":"NO");
  }
  return 0;
}
