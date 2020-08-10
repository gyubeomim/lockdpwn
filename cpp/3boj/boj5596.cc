// @date:              2020.08.10.Mon
// @level:             1
// @category:          Basic
// @description:       시험 점수
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int sum_a=0, sum_b = 0;

  for(int i=0; i<4; i++) {
    int n;
    cin >> n;
    sum_a += n;
  }
  for(int i=0; i<4; i++) {
    int n;
    cin >> n;
    sum_b += n;
  }

  if(sum_a >= sum_b) {
    cout << sum_a << endl;
  }
  else {
    cout << sum_b << endl;
  }

  return 0;
}
