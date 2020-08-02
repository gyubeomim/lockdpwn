// @level:             D2
// @category:          -
// @description:       조교의 성적매기기
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{
  int t;
  int T;

  cin>>T;

  for(t = 1; t <= T; t++) {
    int N,K;
    cin >> N >> K;

    std::vector<std::pair<double,int>> scores;
    scores.clear();

    for(int i=1; i<=N; i++) {
      double a,b,c;
      cin >> a >> b >> c;

      double score = a*0.35 + b*0.45 + c*0.20;
      int rank;
      if(i == K) {
        rank = -1;
      }
      else {
        rank = i;
      }
      scores.push_back(std::make_pair(score, rank));
    }

    std::sort(scores.begin(), scores.end(), [&](const std::pair<double,int> &a,
                                                const std::pair<double,int> &b)
                                            {
                                              return a.first > b.first;
                                            });

    int count=0;
    for(int i=0; i<scores.size(); i++) {
      if(scores[i].second == -1) {
        count = i+1;
        break;
      }
    }

    int n = N / 10;
    // std::cout << "before count: " << count << ", N: " << N << ", n: " << n << ", scores.size(): " << scores.size() << std::endl;

    double k = (double)count / n;
    count = std::ceil(k);

    // std::cout << "after count: " << count << std::endl;

    std::cout << '#' << t << " ";
    switch(count) {
      case 1:
        std::cout << "A+" << std::endl;
        break;
      case 2:
        std::cout << "A0" << std::endl;
        break;
      case 3:
        std::cout << "A-" << std::endl;
        break;
      case 4:
        std::cout << "B+" << std::endl;
        break;
      case 5:
        std::cout << "B0" << std::endl;
        break;
      case 6:
        std::cout << "B-" << std::endl;
        break;
      case 7:
        std::cout << "C+" << std::endl;
        break;
      case 8:
        std::cout << "C0" << std::endl;
        break;
      case 9:
        std::cout << "C-" << std::endl;
        break;
      case 10:
        std::cout << "D0" << std::endl;
        break;
    }
  }

  return 0;
}
