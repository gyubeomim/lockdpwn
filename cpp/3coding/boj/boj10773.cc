// @level:             1
// @category:          Basic
// @description:       10773. 제로
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int K;
  cin >> K;

  vector<int> nums;
  for(int i=0; i<K; i++) {
    int num;
    cin >> num;

    if(num != 0) {
      nums.push_back(num);
    }
    else {
      nums.erase(nums.end()-1);
    }
  }

  int sum=0;
  for(auto it : nums) {
    sum += it;
  }

  cout << sum << endl;
turn 0;
}
