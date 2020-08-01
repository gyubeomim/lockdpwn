/*
  c++ ==> 백준 1181번, 단어정렬
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

bool cmp(const string &a, const string &b) {
  if(a.length() > b.length())
    return true;
  else
    return a > b;
}

int main(int argc, char **argv) {
  vector<string> vs;

  int numString = 0;
  /* string str; */
  /* cin >> numString; */
  /* for (int i=0; i<numString ; i++) { */
  /*   cin >> str; */
  /*   vs.push_back(str); */
  /* } */

  vs.push_back("but");
  vs.push_back("i");
  vs.push_back("wont");
  vs.push_back("hesitate");
  vs.push_back("no");
  vs.push_back("more");
  vs.push_back("no");
  vs.push_back("more");
  vs.push_back("it");
  vs.push_back("cannot");
  vs.push_back("wait");
  vs.push_back("im");
  vs.push_back("yours");

  sort(vs.begin(), vs.end(), cmp);

  for (auto i : vs) {
    std::cout << i << std::endl;
  }

  return 0;
}
