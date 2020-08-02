// @level:             2
// @category:          Brute Force
// @description:       PICNIC
#include <bits/stdc++.h>

using namespace std;

int N;
bool friends[10][10];

int solution(bool taken[10]) {
  int front=-1;

  for(int i=0; i<N; i++) {
    if(!taken[i]) {
      front = i;
      break;
    }
  }

  if(front == -1) {
    return 1;
  }

  int count=0;
  for(int i=front+1; i<N; i++) {
    if(!taken[i] && friends[front][i]) {
      taken[front] = taken[i] = true;
      count += solution(taken);
      taken[front] = taken[i] = false;
    }
  }
  return count;
}

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int T;
  cin >> T;

  while(T--) {
    bool taken[10] = {false};
    memset(friends, false, sizeof(friends));

    int M;
    cin >> N >> M;

    for(int i=0; i<M; i++) {
      int a,b;
      cin >> a >> b;

      friends[a][b] = friends[b][a] = true;
    }

    cout << solution(taken) << endl;
  }

  return 0;
}
