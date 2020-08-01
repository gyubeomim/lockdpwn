// @date:              2020.07.31.Fri
// @level:             1
// @category:          Basic
// @description:       3058. 짝수를 찾아라
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int T;
  cin >> T;

  while(T--) {
    vector<int> nums;
    int sum=0;
    for(int i=0; i<7; i++) {
      int num;
      cin >> num;

      if(num %2 == 0) {
        sum += num;
        nums.push_back(num);
      }
    }

    sort(nums.begin(), nums.end());

    cout << sum << ' ' << nums[0] << '\n';
  }

  return 0;
}
