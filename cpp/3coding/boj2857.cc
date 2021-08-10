// @date:              2020.08.06.Thu
// @level:             1
// @category:          String
// @description:       FBI
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  vector<int> fbis;
  for(int i=1; i<=5; i++) {
    string agent;
    cin >> agent;

    for(int j=0; j<agent.size(); j++) {
      // if(agent.substr(j,3) == "FBI") {
      if(agent.find("FBI") != string::npos) {
        fbis.push_back(i);
        break;
      }
    }
  }

  if(fbis.empty()) {
    cout << "HE GOT AWAY!" << endl;
  }
  else {
    for(auto it : fbis) {
      cout << it << ' ';
    }
  }


  return 0;
}
