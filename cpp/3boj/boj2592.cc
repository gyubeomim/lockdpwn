// @date:              2020.07.27.Mon
// @level:             1
// @category:          Basic
// @description:       2592. 대표값
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main(int argc, char** argv) {
  std::vector<int> nums;
  for(int i=0;i<10;i++) {
    int num;
    cin >> num;
    nums.push_back(num);
  }

  double sum;
  double mean;
  std::map<int,int> most;

  for(auto it : nums) {
    sum += it;
    most[it] += 1;
  }
  mean = sum / nums.size();

  auto most_it = std::max_element(most.begin(), most.end(),
                                  [&](const std::pair<int,int> &a,
                                      const std::pair<int,int> &b) {
                                    return a.second < b.second;
                                  });

  std::cout << mean << std::endl << most_it->first << std::endl;

  return 0;
}
