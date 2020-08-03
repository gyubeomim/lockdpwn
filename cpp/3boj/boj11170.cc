// @level:             1
// @category:          Basic
// @description:       0의 개수
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int T;
  cin >> T;

  while(T--) {
    int N,M;
    cin >> N >> M;

    int answer=0;
    for(int i=N; i<=M; i++) {
      string S = to_string(i);
      for(int j=0; j<S.size(); j++) {
        if(S[j] == '0') {
          answer++;
        }
      }
    }

    cout << answer << endl;
  }

  return 0;
}
