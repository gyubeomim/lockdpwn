// @date:              2020.07.29.Wed
// @level:             1
// @category:          Basic
// @description:       2822. 점수 계산
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  vector<pair<int,int>> scores;

  for(int i=1; i<=8; i++) {
    int score;
    cin >> score;
    scores.push_back(make_pair(score, i));
  }

  sort(scores.begin(), scores.end(), [&](const pair<int,int> &a,
                                         const pair<int,int> &b) {
                                       return a.first > b.first;
                                     });

  int answer=0;
  vector<int> orders;
  for(int i=0; i<5; i++) {
    answer += scores[i].first;
    orders.push_back(scores[i].second);
  }

  sort(orders.begin(), orders.end());

  cout << answer << '\n';
  for(auto it : orders) {
    cout << it << ' ';
  }

  return 0;
}
