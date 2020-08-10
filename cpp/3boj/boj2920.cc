// @date:              2020.08.10.Mon
// @level:             1
// @category:          Basic
// @description:       음계
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int prev_n=0;
  int des_count=0, asc_count = 0;

  bool is_mixed = false;
  for(int i=0; i<8; i++) {
    int n;
    cin >> n;

    if(prev_n==0) {
      prev_n = n;
    }
    else {
      if(prev_n - n == 1) {
        des_count += 1;
      }
      else if(prev_n - n == -1) {
        asc_count += 1;
      }
      else {
        is_mixed = true;
      }
      prev_n = n;
    }
  }

  if(des_count == 7) {
    cout << "descending" << endl;
  }
  else if(asc_count == 7) {
    cout << "ascending" << endl;
  }
  else {
    cout << "mixed" << endl;
  }

  return 0;
}
