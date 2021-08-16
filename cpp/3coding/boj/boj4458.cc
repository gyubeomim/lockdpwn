// @level:             1
// @category:          String
// @description:       4458. 첫 글자를 대문자로
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int N;
  cin >> N;
  cin.ignore();
  string S;
  for(int i=0; i<N; i++) {
    getline(cin, S);

    if(S[0] >= 'a' && S[0] <= 'z') {
      S[0] -= 32;
    }
    for(int j=0; j<S.size(); j++) {
      if(S[j] == ' ') {
        if(S[j+1]=='a' && S[j+2]=='n' && S[j+3]=='d') {
          continue;
        }
        else if(S[j+1]=='o' && S[j+2]=='f') {
          continue;
        }
        else if(S[j+1] >= 'a' && S[j+1] <= 'z') {
          S[j+1] -= 32;
        }
      }
    }
    cout << S << endl;
  }

  return 0;
}
