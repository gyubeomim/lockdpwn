// @level:             D2
// @category:          Simulation
// @description:       어디에 단어가 들어갈 수 있을까
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  int t;
  int T;

  cin>>T;

  for(t=1; t<=T; t++) {
    int N,K;
    cin >> N >> K;

    int map[15][15]={0};
    for(int i=0; i<N; i++) {
      for(int j=0; j<N; j++) {
        cin >> map[i][j];
      }
    }

    int answer =0;
    for(int i=0; i<N; i++) {
      for(int j=0; j<N; j++) {
        bool found_v=false;
        bool found_h=false;

        // step 1
        int count_h = 0;
        for(int k=0; k<K; k++) {
          if(i+k < N && map[i+k][j] == 1) {
            count_h += 1;
          }
        }
        if(count_h == K) {
          found_v = true;
        }

        int count_v = 0;
        for(int k=0; k<K; k++) {
          if(j+k < N && map[i][j+k] == 1) {
            count_v += 1;
          }
        }
        if(count_v == K) {
          found_h = true;
        }

        // step 2
        if(found_v) {
          if(i+K < N && map[i+K][j] == 1) {
            found_v = false;
          }
        }

        if(found_h) {
          if(j+K < N && map[i][j+K] == 1) {
            found_h = false;
          }
        }

        // step 3
        if(i-1 >= 0 && map[i-1][j] == 1) {
          found_v = false;
        }

        if(j-1 >= 0 && map[i][j-1] == 1) {
          found_h = false;
        }

        if(found_v || found_h) {
          if((found_v && !found_h) || (!found_v && found_h)) {
            answer += 1;
          }
          else {
            answer += 2;
          }
        }
      }
    }

    std::cout << '#' << t << " " << answer << '\n';
  }

  return 0;
}
