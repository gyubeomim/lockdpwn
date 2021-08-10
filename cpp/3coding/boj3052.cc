// @date:              2020.07.28.Tue
// @level:             1
// @category:          Basic
// @description:       3052. 나머지
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main(int argc, char** argv) {
  std::map<int,int> mod;

  for(int i=0;i<10;i++) {
    int num;
    cin >> num;

    mod[num%42] += 1;
  }

  int answer=0;
  for(auto it : mod) {
    if(it.second > 0) {
      answer += 1;
    }
  }

  std::cout << answer << std::endl;

  return 0;
}
