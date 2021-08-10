// @date:              2020.07.28.Tue
// @level:             1
// @category:          Basic
// @description:       3460. 이진수
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

std::string GetBinary(int n) {
  std::string result;

  while(n > 0) {
    result.insert(0, std::to_string(n%2));
    n /= 2;
  }

  return result;
}

int main(int argc, char** argv) {
  int T;
  cin >> T;

  while(T--) {
    int n;
    cin>>n;

    std::string bin = GetBinary(n);

    std::reverse(bin.begin(), bin.end());
    for(int i=0;i<bin.size();i++) {
      if( (bin[i] - '0') == 1) {
        cout << i << ' ';
      }
    }
    
  }

  return 0;
}
