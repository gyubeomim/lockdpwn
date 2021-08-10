// @level:             1
// @category:          Basic
// @description:       5176. 대회 자리
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int T;
  cin >> T;

  while(T--) {
    int P,M;
    cin >> P >> M;

    vector<int> nums(P,0);
    int answer = 0;
    for(int i=0; i<P; i++) {
      int p;
      cin >> p;
      if(nums[p-1] == 0) {
        nums[p-1] = 1;
      }
      else {
        answer += 1;
      }
    }

    cout << answer << endl;
  }

  return 0;
}
