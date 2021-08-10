// @date:              2020.08.10.Mon
// @level:             1
// @category:          Basic
// @description:       과제 안 내신분..?
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  map<int,int> homework;
  for(int i=0; i<28; i++) {
    int id;
    cin >> id;

    homework[id] += 1;
  }

  for(int i=1; i<=30; i++) {
    if(homework[i] == 0) {
      cout << i << endl;
    }
  }

  return 0;
}
