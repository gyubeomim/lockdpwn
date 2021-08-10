// @date:              2020.07.28.Tue
// @level:             1
// @category:          Basic
// @description:       10807. 개수 세기
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int N;
  cin >> N;

  std::vector<int> nums;
  for(int i=0;i<N;i++) {
    int num;
    cin >> num;
    nums.push_back(num);
  }

  int v;
  cin >> v;

  int answer=0;
  for(auto it : nums) {
    if(it == v) {
      answer += 1;
    }
  }
  std::cout << answer << std::endl;

  return 0;
}
