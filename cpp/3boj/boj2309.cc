// @date:              2020.07.30.Thu
// @level:             1
// @category:          Brute Force
// @description:       2309. 일곱 난쟁이
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int sum=0;
  vector<int> heights;
  for(int i=0;i<9;i++) {
    int height;
    cin >> height;
    heights.push_back(height);
    sum += height;
  }

  for(int i=0; i<heights.size()-1; i++) {
    for(int j=i+1; j<heights.size(); j++) {
      int a = heights[i];
      int b = heights[j];

      if(sum - a - b == 100) {
        heights.erase(heights.begin()+j);
        heights.erase(heights.begin()+i);
      }
    }
  }

  sort(heights.begin(), heights.end());

  for(auto it : heights) {
    cout << it << endl;
  }

  return 0;
}
