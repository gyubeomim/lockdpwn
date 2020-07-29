// @date:              2020.07.29.Wed
// @level:             1
// @category:          Basic
// @description:       5054. 주차의 신
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int T;
  cin >> T;

  while(T--) {
    int N;
    cin >> N;

    vector<int> shops;
    for(int i=0; i<N; i++) {
      int shop;
      cin >> shop;
      shops.push_back(shop);
    }

    sort(shops.begin(), shops.end());

    int answer=0;
    for(int i=1; i<shops.size(); i++) {
      answer += abs(shops[i-1] - shops[i]);
    }
    answer += abs(shops[0] - shops[N-1]);

    cout << answer << '\n';
  }

  return 0;
}
