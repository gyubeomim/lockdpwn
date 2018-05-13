/*
  c++ ==> 백준 2217, 로프의 문제를 푼 코드
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool Greater(int left, int right) {
  return left > right;
}

int main(int argc, char **argv) {
  int k=0, tmp=0;
  int result = 0;
  vector<int> rope;

  cin >> k;

  for(int i=0; i<k; i++) {
    cin >> tmp;
    rope.push_back(tmp);
  }

  sort(rope.begin(), rope.end(), Greater);

  for(auto i=1; i<=k; i++) {
    result = std::max(result, rope.at(i-1)*i);
  }

  cout << result;

  return 0;
}
