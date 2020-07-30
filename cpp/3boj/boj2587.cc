// @date:              2020.07.30.Thu
// @level:             1
// @category:          Basic
// @description:       2587. 대표값2
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  vector<int> nums;
  int sum=0;
  int mean=0;

  for(int i=0; i<5; i++) {
    int num;
    cin >> num;
    nums.push_back(num);
    sum += num;
  }
  mean = sum / 5;

  sort(nums.begin(), nums.end());

  int median = nums[2];

  cout << mean << '\n';
  cout << median << '\n';

  return 0;
}
