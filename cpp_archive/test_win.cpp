






















#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int d[10001];
int A[10001];
int sum[10001];

int main(int argc, char const *argv[]) {
  int n;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    scanf("%d", &A[i]);
  }

  for (int i = 1; i <= n; i++) {
    d[i] = 1;
    sum[i] = A[i];
  }

  vector<int> v;
  vector<vector<int>> vec;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j < i; j++) {
      if (A[i] > A[j]) {
        d[i] = std::max({d[i], d[j] + 1});
        v.push_back(j);
      }
    }
    if(i==1)
      v.push_back(1);

    vec.push_back(v);
    if (!v.empty()) v.clear();
  }

  for(int i=2; i<=vec.size(); i++) {
    for(int j=1; j<=vec.at(i-1).size(); j++)
      sum[i] += A[vec.at(i-1).at(j-1)];
  }

  // cout << "---------------------" << endl;
  // for (auto it : vec) {
  //   for (auto it2 : it) {
  //     cout << it2 << " ";
  //   }
  //   cout << endl;
  // }
  // cout << "---------------------" << endl;
  // for (auto it : d) {
  //   if (it != 0)
  //     cout << it << " ";
  // }
  // cout << endl;

  // for (auto it : sum) {
  //   if (it != 0)
  //     cout << it << " ";
  // }
  // cout << endl;

  cout << *std::max_element(sum, sum + n + 1) << '\n';

  return 0;
}
