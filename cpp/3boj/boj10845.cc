// @date:              2020.08.06.Thu
// @level:             1
// @category:          Queue
// @description:       큐
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int N;
  cin >> N;

  queue<int> Q;

  cin.ignore(0);

  for(int i=0; i<N; i++) {
    string cmd;
    cin >> cmd;

    if(cmd == "push") {
      int n;
      cin >> n;
      Q.push(n);
    }
    else if(cmd == "front") {
      if(Q.empty()) {
        cout << -1 << endl;
      }
      else {
        cout << Q.front() << endl;
      }
    }
    else if(cmd == "back") {
      if(Q.empty()) {
        cout << -1 << endl;
      }
      else {
        cout << Q.back() << endl;
      }
    }
    else if(cmd == "size") {
      cout << Q.size() << endl;
    }
    else if(cmd == "empty") {
      if(Q.empty()) {
        cout << 1 << endl;
      }
      else {
        cout << 0 << endl;
      }
    }
    else if(cmd == "pop") {
      if(Q.empty()) {
        cout << -1 << endl;
      }
      else {
        cout << Q.front() << endl;
        Q.pop();
      }
    }
  }

  return 0;
}
