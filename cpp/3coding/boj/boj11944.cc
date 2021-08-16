// @date:              2020.08.01.Sat
// @level:             1
// @category:          Basic
// @description:       11944. NN
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int N,M;
  cin>>N>>M;

  string str = to_string(N);

  int i=0;
  int n_count=0;
  while(true) {
    if(i > str.size()-1) {
      n_count += 1;
      i = 0;
    }

    if(n_count == N) {
      break;
    }

    cout << str[i++];

    M--;
    if(M<=0) {
      break;
    }
  }


  return 0;
}
