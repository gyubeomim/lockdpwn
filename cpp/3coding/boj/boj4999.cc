// @date:              2020.08.10.Mon
// @level:             1
// @category:          Basic
// @description:       아!
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  string me;
  string doctor;

  cin >> me;
  cin >> doctor;

  if(me.size() >= doctor.size()) {
    cout << "go" << endl;
  }
  else {
    cout << "no" << endl;
  }

  return 0;
}
