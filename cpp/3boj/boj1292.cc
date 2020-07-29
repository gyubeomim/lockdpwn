// @date:              2020.07.28.Tue
// @level:             1
// @category:          Basic
// @description:       1292 쉽게 푸는 문제
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
  std::vector<int> nums;

  for(int i=1;i<=1000;i++) {
    for(int j=0; j<i; j++) {
      nums.push_back(i);
    }
  }

  int A,B;
  cin>>A>>B;

  long long answer=0;
  for(int i=A-1; i<B; i++) {
    answer += nums.at(i);
  }

  std::cout << answer << std::endl;


  return 0;
}
