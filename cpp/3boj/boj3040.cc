// @date:              2020.07.31.Fri
// @level:             1
// @category:          Brute Force
// @description:       3040. 백설 공주와 일곱 난쟁이
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  vector<int> nums;
  int sum =0;
  for(int i=0; i<9; i++) {
    int num;
    cin >> num;
    nums.push_back(num);
    sum += num;
  }

  for(int i=0; i<nums.size()-1; i++) {
    for(int j=i+1; j<nums.size(); j++) {
      if(sum - nums[i] - nums[j] == 100) {
        nums.erase(nums.begin() + j);
        nums.erase(nums.begin() + i);
      }
    }
  }

  sort(nums.begin(), nums.end());

  for(auto it : nums) {
    cout << it << endl;
  }


  return 0;
}
