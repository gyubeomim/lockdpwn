/*
 * #+DESCRIPTION:       백준 1939, 중량제한 문제를 푼 코드
 * #+CATEGORY:          Binary Search
 * #+TIME_COMPLEXITY:   -
 * #+LEVEL:             -
 * #+FROM:              중급1 이분탐색으로 정답찾기 part 2
 * #+DATE:              2018-06-24-일
 * #+AUTHOR:            Edward Im (gyurse@gmail.com)
 */
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<pair<int,int>> a[10001];
bool c[10001];
int n,m;
int st, ed;

bool dfs(int node, int limit) {
  if(c[node]) return false;

  c[node] = true;
  if(node == ed)
    return true;

  for(auto &p : a[node]) {
    int next = p.first;
    int cost = p.second;

    if(cost >= limit)
      if(dfs(next, limit))
        return true;
  }
  return false;
}

int main() {
  cin >> n >> m;

  while(m--) {
    int x,y,z;
    cin >> x >> y >> z;
    a[x].push_back(make_pair(y,z));
    a[y].push_back(make_pair(x,z));
  }

  cin >> st >> ed;
  int left, right;
  left = 1;
  right = 1000000000;
  int ans = 0;

  while(left <= right) {
    int mid = (left+right)/2;
    memset(c, false, sizeof(c));

    if(dfs(st, mid)) {
      ans = mid;
      left = mid+1;
    }
    else
      right = mid-1;
  }
  cout << ans << '\n';
  return 0;
}
