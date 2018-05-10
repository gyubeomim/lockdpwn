#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool cmp(const vector<string> &a, const vector<string> &b){
  if(a > b)
    return true;
  else
    return a < b;
}

int main(int argc, char **argv){
  vector<string> vs;

  int numString = 0;
  string str;
  cin >> numString;

  for (int i=0; i<numString ; i++) {
    cin >> str;
    vs.push_back(str);
  }

  sort(vs.begin(), vs.end());

  for (auto i : vs) {
    std::cout << i << std::endl;
  }

  return 0;
}
