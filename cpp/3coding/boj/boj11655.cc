// @level:             1
// @category:          Basic
// @description:       ROT13
#include <bits/stdc++.h>

using namespace std;

string PerformROT13(string S) {
  string result;
  result.resize(S.size());

  for(int i=0; i<S.size(); i++) {
    if(S[i] >= '0' && S[i] <='9') {
      result[i] = S[i];
    }
    else if(S[i] == ' ') {
      result[i] = S[i];
    }
    else if(S[i] >= 'a' && S[i] <= 'z'){
      unsigned char c = static_cast<unsigned char>(S[i] + 13);
      if(c > 'z') {
        c -= 26;
      }
      result[i] = c;
    }
    else if(S[i] >= 'A' && S[i] <= 'Z'){
      unsigned char c = static_cast<unsigned char>(S[i] + 13);
      if(c > 'Z') {
        c -= 26;
      }
      result[i] = c;
    }
  }

  return result;
}

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  string S;
  getline(cin, S);

  string answer = PerformROT13(S);
  cout << answer << endl;

  return 0;
}
