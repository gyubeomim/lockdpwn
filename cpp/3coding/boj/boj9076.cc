// @date:              2020.07.30.Thu
// @level:             1
// @category:          Basic
// @description:       9076. 점수 집계
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int T;
  cin >> T;

  while(T--) {
    vector<int> nums;
    for(int i=0; i<5; i++) {
      int num;
      cin >> num;
      nums.push_back(num);
    }

    sort(nums.begin(), nums.end());
    nums.erase(nums.end()-1);
    nums.erase(nums.begin());

    int min_n = nums.front();
    int max_n = nums.back();

    if(max_n - min_n >= 4) {
      cout << "KIN" << endl;
    }
    else {
      int sum=0;
      for(auto it : nums) {
        sum += it;
      }
      cout << sum << endl;
    }

  }

  return 0;
}
