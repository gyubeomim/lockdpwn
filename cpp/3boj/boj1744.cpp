/*
 * #+DESCRIPTION:  백준 1744, 수 묶기
 * #+CATEGORY:     GREEDY
 * #+LEVEL:        -
 * #+FROM:         중급1 그리디 알고리즘 part 2
 */
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int n;
  vector<int> plus;
  vector<int> minus;
  cin >> n;

  int zero=0;
  int one=0;

  for(int i=0; i<n; i++) {
    int x;
    cin >> x;

    if(x==1)
      one += 1;
    else if(x>0)
      plus.push_back(x);
    else if(x<0)
      minus.push_back(x);
    else
      zero += 1;
  }

  sort(plus.begin(), plus.end());
  reverse(plus.begin(), plus.end());
  sort(minus.begin(), minus.end());

  // ed: 홀수개만큼 들어가 있는 경우
  if(plus.size()%2 == 1)
    plus.push_back(1);              // ed: 양수는 1을
  if(minus.size()%2 == 1)
    minus.push_back(zero>0 ? 0:1);  // ed: 음수는 0의 개수에 따라서 0,1을 넣는다

  int ans=one;
  for(int i=0; i<plus.size(); i+=2) {
    ans += plus[i]*plus[i+1];
  }
  for(int i=0; i<minus.size(); i+=2) {
    ans += minus[i]*minus[i+1];
  }
  cout << ans << '\n';

  return 0;
}
