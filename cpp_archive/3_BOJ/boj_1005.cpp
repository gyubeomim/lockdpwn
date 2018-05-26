/*
  c++ ==> 백준 1005, ACM Craft 문제를 푼 정답 코드
                    위상정렬을 사용해서 문제를 풀었다


  code from [http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220620723528&parentCategoryNo=271&categoryNo=303&viewDate=&isShowPopularPosts=false&from=postList]
*/
#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int T;
  cin >> T;

  for(int t=0; t<T; t++) {
    // pre: 선행자의 개수, suc: 후행자의 목록
    int N,K,W,time[1000], pre[1000] = {0};
    vector<int> suc[1000];
    cin >> N >> K;

    for(int i=0; i<N; i++)
      cin >> *(time+i);

    for(int i=0; i<K; i++) {
      int X,Y;
      cin >> X >> Y;
      suc[X-1].push_back(Y-1);
      pre[Y-1]++;
    }
    cin >> W;
    W--;

    // result: 해당 건물을 짓기 시작하는 데 걸리는 최소 시간
    int result[1000] = {0};
    queue<int> Q;
    // 선행자가 하나도 없는 노드들을 먼저 큐에 push
    for(int i=0; i<N; i++)
      if(!pre[i]) Q.push(i);

    // W번 건물의 선행자가 하나도 없을 때까지
    while(pre[W] > 0) {
      int u = Q.front();
      Q.pop();
      // 모든 후행자 건물의 최소 건설시작시간을 갱신한다
      for(int next: suc[u]) {
        result[next] = max(result[next], result[u]+time[u]);
        if(--pre[next] == 0) Q.push(next);
      }
    }
    // 목표 건물을 짓는데 걸리는 시간도 더한다
    cout << result[W]+time[W] << endl;
  }
  return 0;
}
