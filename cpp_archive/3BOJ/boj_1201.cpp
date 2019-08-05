/*
 * #+DESCRIPTION:  백준 1201, NMK 문제를 푼 코드
 * #+CATEGORY:     GREEDY
 * #+LEVEL:        -
 * #+FROM:         중급1 그리디 알고리즘 part 2
 * #+DATE:         2018-06-21-목
 * #+AUTHOR:       Edward Im (gyurse@gmail.com)
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
  정답은 M+K-1 <= N <= MK 인 경우에만 존재한다 (중급1 그리디 알고리즘 part 2 참고)

   1) 1부터 N까지 수를 오름차순으로 적는다
   2) 수를 M등분한다. 이 때 그룹에 들어있는 수는 K보다 작거나 같아야 하며 적어도 한 그룹은 들어있는 수의 개수가 K개여야 한다
   3) 각 그룹에 들어있는 수의 순서를 뒤집는다
 */

int main() {
  int n,m,k;
  cin >> n >> m >> k;

  vector<int> a(n);
  if(m+k-1 <= n && n <= m*k) {
    for(int i=0; i<n; i++) {
      a[i] = i+1;
    }

    // ed: 그룹의 경계를 g에 넣어준다
    vector<int> g;
    g.push_back(0);
    g.push_back(k);
    n -= k;
    m -= 1;

    int gs = m==0 ? 1 : n/m;
    int r = m==0 ? 0 : n%m;

    // ed: 그룹의 크기를 각각 결정한다
    //     랜덤으로 그룹의 크기를 결정하는게 아니라 대부분 k개이고 k--순으로 그룹의 크기를 결정한다)
    for(int i=0; i<m; i++) {
      g.push_back(g.back() + gs + (r>0 ? 1:0));
      if(r > 0)
        r -= 1;
    }

    // ed: 그룹의 크기를 결정한 다음 각 그룹을 뒤집어준다
    for(int i=0; i<g.size()-1; i++) {
      reverse(a.begin()+g[i], a.begin()+g[i+1]);
    }

    // ed: 정답을 출력한다
    for(int i=0; i<a.size(); i++) {
      cout << a[i] << ' ';
    }
    cout << '\n';
  }
  else
    cout << "-1\n";

  return 0;
}
