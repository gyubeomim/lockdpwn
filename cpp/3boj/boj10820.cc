// @date:              2020.08.06.Thu
// @level:             1
// @category:          Basic
// @description:       문자열 분석
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  while(true) {
    string S;
    getline(cin, S);

    if(S.empty()) {
      break;
    }
    int number_count=0;
    int lower_count=0;
    int upper_count=0;
    int space_count=0;

    for(int i=0; i<S.size(); i++) {
      char c = S[i];
      if(c >= '0' && c <= '9') {
        number_count++;
      }
      else if(c >= 'a' && c <= 'z') {
        lower_count++;
      }
      else if(c >= 'A' && c <= 'Z') {
        upper_count++;
      }
      else if(c == ' ') {
        space_count++;
      }
    }

    cout << lower_count << ' ' << upper_count << ' ' << number_count << ' ' << space_count << endl;

  }
  return 0;
}
