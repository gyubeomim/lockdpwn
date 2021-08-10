// @date:              2020.08.10.Mon
// @level:             1
// @category:          String
// @description:       파일 완전 삭제
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int N;
  cin >> N;

  string S1, S2;
  cin >> S1;
  cin >> S2;

  if(N%2 == 0) {
    if (S1 == S2) {
      cout << "Deletion succeeded" << endl;
    }
    else {
      cout << "Deletion failed" << endl;
    }
  }
  else if(N%2 == 1) {
    for(int i=0; i<S1.size(); i++) {
      if(S1[i] == '1') {
        S1[i] = '0';
      }
      else {
        S1[i] = '1';
      }
    }

    if(S1 == S2) {
      cout << "Deletion succeeded" << endl;
    }
    else {
      cout << "Deletion failed" << endl;
    }
  }

  return 0;
}
