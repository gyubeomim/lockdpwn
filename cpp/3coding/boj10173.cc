// @date:              2020.08.10.Mon
// @level:             1
// @category:          String
// @description:       니모를 찾아서
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

    if(S == "EOI") {
      break;
    }

    transform(S.begin(), S.end(), S.begin(), ::tolower);
   
    if(S.find("nemo") != string::npos) {
      cout << "Found" << endl;
    }
    else {
      cout << "Missing" << endl;
    }

  }

  return 0;
}
