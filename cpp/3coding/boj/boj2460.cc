// @date:              2020.07.27.Mon
// @level:             1
// @category:          Basic
// @description:       2460. 지능형기차
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  std::vector<int> train;

  for(int i=0;i<10;i++) {
    int plus, minus;
    cin >> minus >> plus;

    if(i==0) {
      train.push_back(plus - minus);
    }
    else {
      train.push_back(train[i-1] + plus - minus);
    }
  }

  auto answer = std::max_element(train.begin(), train.end());
  cout << *answer;

  return 0;
}
