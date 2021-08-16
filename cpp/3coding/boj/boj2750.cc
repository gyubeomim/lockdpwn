// @date:              2020.07.29.Wed
// @level:             1
// @category:          Sort
// @description:       2750. 수 정렬하기
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

  sort(nums.begin(), nums.end());

  for(auto it : nums) {
    cout << it << endl;
  }

  return 0;
}
