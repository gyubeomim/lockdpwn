/*
  c++ ==> 백준 4344, 평균은 넘겠지 문제를 벡터를 사용해서 푼 정답코드


  code from [http://zong.tistory.com/2]
*/
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
  int c=0, n=0;
  cin >> c;

  for(int t=0; t<c; t++) {
    int count=0;
    cin >> n;
    vector<int> scores;

    for(int i=0; i<n; i++ ) {
      int score=0;
      cin >> score;
      scores.push_back(score);
    }

    double avg = accumulate(scores.begin(), scores.end(), 0.0) / scores.size();

    while(!scores.empty()) {
      int back = scores.back();
      scores.pop_back();

      if(back > avg)
        count++;
    }
    printf("%.3lf%%\n", (double)count/n*100.0);
  }

  return 0;
}
