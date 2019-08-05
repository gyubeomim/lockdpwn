/*
  c++ ==> 백준 5430, AC 문제를 푼 코드 [런타임에러]

  dequeue를 사용해 풀려고 시도했으나 런타임에러가 나와서 풀지 못한 코드
*/
#include <iostream>
#include <cstdio>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
  int T;
  cin >> T;

  while(T--) {
    string str;
    int arrayLen;
    string tmp;
    bool b_error = false, b_rev = false;

    cin >> str;
    cin >> arrayLen;
    cin >> tmp;

    deque<int> dq(arrayLen);

    if(tmp.empty()) {
      cout << "error" << endl;
      b_error = true;
      continue;
    }

    for(int i=0; i<tmp.size()/2; i++) {
      dq[i] = tmp[2*i + 1] - '0';
    }

    for(int i=0; i<str.size(); i++) {
      switch(str[i]) {
        case 'R':
          b_rev = !b_rev;
          break;
        case 'D':
          if(dq.empty()) {
            cout << "error" << endl;
            b_error = true;
            break;
          }

          if(b_rev)
            dq.pop_back();
          else
            dq.pop_front();

          break;
      }
    }
    if(b_rev)
      reverse(dq.begin(), dq.end());

    if(!b_error) {
      cout << "[";
      for(auto it : dq) {

        if(it != dq.back())
          cout << it << ",";
        else
          cout << it;
      }
      cout << "]" << endl;
      dq.clear();
    }
  }
  return 0;
}
