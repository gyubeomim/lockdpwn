// @date:              2020.07.27.Mon
// @level:             1
// @category:          Basic
// @description:       2577. 숫자의 개수
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  int a,b,c;
  cin >> a >> b >> c;

  int mult = a*b*c;
  std::string mult_str = std::to_string(mult);

  std::vector<int> answer(10,0);

  for(int i=0; i<mult_str.size(); i++) {
    int num = mult_str[i] - '0';
    answer[num] += 1;
  }

  for(auto it : answer) {
    std::cout << it << std::endl;
  }

  return 0;
}
