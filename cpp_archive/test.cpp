#include <iostream>
#include <queue>
using namespace std;

bool ans[201];
bool check[201][201];

int main() {
  int a,b,c;
  cin >> a >> b >> c;

  int sum = c;
  queue<pair<int,int>> q;
  q.push(make_pair(0,0));

  check[0][0] = true;
  ans[c] = true;

  while(!q.empty()) {

  }


  return 0;
}
