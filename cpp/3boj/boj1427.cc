// @date:              2020.07.30.Thu
// @level:             1
// @category:          Sort
// @description:       1427. 소트인사이드
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  string str;
  cin >> str;

  sort(str.begin(), str.end(), [&](const char &a,
                                   const char &b)
                               {
                                 return a-'0' > b-'0';
                               });

  cout << str << endl;

  return 0;
}
