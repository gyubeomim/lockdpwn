// @date:              2020.07.26.Sun
// @level:             D2
// @level:             -
// @description:       2001.
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
  int T;
  cin >> T;

  for(int t=1; t<=T; t++) {
    int map[15][15];

    int N,M;
    cin >> N >> M;

    for(int i=0; i<N; i++) {
      for(int j=0; j<N; j++) {
        int num;
        cin >> num;
        map[i][j] = num;
      }
    }

    int max_sum = 0;
    for(int i=0; i<N; i++) {
      for(int j=0; j<N; j++) {
        int sum=0;

        for(int r=0; r<M; r++) {
          for(int c=0; c<M; c++) {

            if(i+r < N && j+c < N) {
              sum += map[i+r][j+c];
            }

          }
        }

        if(max_sum < sum) {
          max_sum = sum;
        }

      }
    }

    cout << '#' << t << ' ' << max_sum << '\n';
  }

  return 0;
}
