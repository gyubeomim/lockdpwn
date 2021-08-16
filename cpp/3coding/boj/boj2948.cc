// @level:             1
// @category:          Basic
// @description:       2009년
#include <bits/stdc++.h>

using namespace std;

const int day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
const string date[7] = {"Thursday", "Friday", "Saturday", "Sunday","Monday", "Tuesday", "Wednesday"};

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int M, D;
  cin >> D >> M;

  int d=0;
  while(M>1) {
    d += day[M-2];
    M--;
  }

  d += D - 1;
  d %= 7;

  cout << date[d] << endl;


  return 0;
}
