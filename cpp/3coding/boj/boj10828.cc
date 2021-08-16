// @date:              2020.08.06.Thu
// @level:             1
// @category:          Stack
// @description:       스택
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  stack<int> s;

  int N;
  cin >> N;
  cin.ignore(0);

  for(int i=0; i<=N; i++) {
    string cmd;
    getline(cin, cmd);

    if(cmd == "top") {
      if(s.empty()) {
        cout << -1 << endl;
      }
      else {
        cout << s.top() << endl;
      }
    }
    else if(cmd == "size") {
      cout << s.size() << endl;
    }
    else if(cmd == "empty") {
      if(s.empty()) { 
        cout << 1 << endl;
      }
      else {
        cout << 0 << endl;
      }
    }
    else if(cmd == "pop") {
      if(s.empty()) {
        cout << -1 << endl;
      }
      else {
        cout << s.top() << endl;
        s.pop();
      }
    }
    else if(cmd.substr(0,4) == "push") {
      string num = cmd.substr(5);
      s.push(stoi(num,0));
    }
  }

  return 0;
}
