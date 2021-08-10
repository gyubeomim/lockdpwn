// @date:              2020.07.29.Wed
// @level:             1
// @category:          Basic
// @description:       2752. 세수정렬
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int a,b,c;
  cin >> a >> b >> c;

  int maxnum, minnum, midnum;
  if(a > b && a > c) {
    maxnum = a;
    if(b > c) {
      midnum = b;
      minnum = c;
    }
    else {
      midnum = c;
      minnum = b;
    }
  }
  else if (b > a && b > c) {
    maxnum = b;
    if(a > c) {
      midnum = a;
      minnum = c;
    }
    else {
      midnum = c;
      minnum = a;
    }
  }
  else if (c > a && c > b) {
    maxnum = c;
    if(a > b) {
      midnum = a;
      minnum = b;
    }
    else {
      midnum = b;
      minnum = a;
    }
  }

  cout << minnum << ' ' << midnum << ' ' << maxnum << endl;


  return 0;
}
