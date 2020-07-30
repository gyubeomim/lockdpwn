// @date:              2020.07.30.Thu
// @level:             1
// @category:          Sort
// @description:       11650. 좌표 정렬하기
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  vector<pair<int, int>> coords;

  int N;
  cin >> N;

  for(int i=0; i<N; i++) {
    int x,y;
    cin >> x >> y;
    coords.push_back(make_pair(x,y));
  }

  sort(coords.begin(), coords.end(), [](const pair<int,int> &a,
                                        const pair<int,int> &b) {
                                       if(a.first != b.first) {
                                         return a.first < b.first;
                                       }
                                       else {
                                         return a.second < b.second;
                                       }
                                     });

      for(auto it : coords) {
        cout << it.first << ' ' << it.second << '\n';
      }
  return 0;
}
