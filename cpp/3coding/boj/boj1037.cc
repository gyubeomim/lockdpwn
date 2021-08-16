// @date:              2020.07.29.Wed
// @level:             1
// @category:          Basic
// @description:       1037. 약수
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

  vector<int> nums;
  for(int i=0; i<N; i++) {
    int num;
    cin >> num;

    nums.push_back(num);
  }

  auto maxnum = max_element(nums.begin(), nums.end());
  auto minnum = min_element(nums.begin(), nums.end());

  int answer = *maxnum * *minnum;

  cout << answer << '\n';

  return 0;
}
