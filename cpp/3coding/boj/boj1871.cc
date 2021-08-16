// @date:              2020.08.10.Mon
// @level:             1
// @category:          Basic
// @description:       좋은 자동차 번호판
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int T;
  cin >> T;

  while(T--) {
    string S;
    cin >> S;

    string alphabet = S.substr(0,3);
    string number = S.substr(4,4);

    int value_alphabet = (alphabet[0]-'A')*26*26 + (alphabet[1]-'A')*26 + (alphabet[2]-'A');
    int value_number = stoi(number);

    bool is_good=false;
    if(abs(value_alphabet - value_number) <= 100) {
      is_good = true;
    }

    if(is_good) {
      cout << "nice" << endl;
    }
    else {
      cout << "not nice" << endl;
    }
  }

  return 0;
}
