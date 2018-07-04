/*
 * #+DESCRIPTION:       백준 6603, 로또 문제를 푼 코드, 순열함수(next_permutation)로 조합을 구하는 문제와 같다. 7C1, 8C6
 * #+CATEGORY:          PERMUTATION, EXAUSTIVE SEARCH
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              중급1 완전탐색1 순열 사용하기
 * #+DATE:              2018-06-27-수
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  while(true) {
    int n;
    cin >> n;

    if(n==0) break;

    vector<int> a(n);
    for(int i=0; i<n; i++)
      cin >> a[i];

    vector<int> d;
    for(int i=0; i<n-6; i++)
      d.push_back(0);

    for(int i=0; i<6; i++)
      d.push_back(1);

    vector<vector<int>> ans;

    do {
      vector<int> current;
      for(int i=0; i<n; i++) {
        if(d[i] == 1)
          current.push_back(a[i]);
      }
      ans.push_back(current);
    } while (next_permutation(d.begin(), d.end()));

    sort(ans.begin(), ans.end());
    for(auto &v : ans) {
      for(int i=0; i<v.size(); i++) {
        cout << v[i] << ' ';
      }
      cout << '\n';
    }
    cout << '\n';
  }

  return 0;
}
