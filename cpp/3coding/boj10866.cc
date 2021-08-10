// @date:              2020.08.06.Thu
// @level:             1
// @category:          Deque
// @description:       덱
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int N;
  cin >> N;

  deque<int> DQ;

  cin.ignore(0);

  for(int i=0; i<N; i++) {
    string cmd;
    cin >> cmd;

    if(cmd == "push_front") {
      int n;
      cin >> n;
      DQ.push_front(n);
    }
    else if(cmd == "push_back") {
      int n;
      cin >> n;
      DQ.push_back(n);
    }
    else if(cmd == "front") {
      if(DQ.empty()) {
        cout << -1 << endl;
      }
      else {
        cout << DQ.front() << endl;
      }
    }
    else if(cmd == "back") {
      if(DQ.empty()) {
        cout << -1 << endl;
      }
      else {
        cout << DQ.back() << endl;
      }
    }
    else if(cmd == "size") {
      cout << DQ.size() << endl;
    }
    else if(cmd == "empty") {
      if(DQ.empty()) {
        cout << 1 << endl;
      }
      else {
        cout << 0 << endl;
      }
    }
    else if(cmd == "pop_front") {
      if(DQ.empty()) {
        cout << -1 << endl;
      }
      else {
        cout << DQ.front() << endl;
        DQ.pop_front();
      }
    }
    else if(cmd == "pop_back") {
      if(DQ.empty()) {
        cout << -1 << endl;
      }
      else {
        cout << DQ.back() << endl;
        DQ.pop_back();
      }
    }
  }

  return 0;
}
