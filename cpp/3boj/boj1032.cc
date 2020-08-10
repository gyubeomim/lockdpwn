// @date:              2020.08.10.Mon
// @level:             1
// @category:          String
// @description:       명령 프롬프트
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int N;
  cin >> N;

  vector<string> fns;
  for(int i=0; i<N; i++) {
    string fn;
    cin >> fn;
    fns.push_back(fn);
  }

  string answer = fns[0];
  for(int i=1; i<fns.size(); i++) {
    for(int j=0; j<answer.size(); j++) {
      if(fns[i][j] != answer[j]) {
        answer[j] = '?';
      }
    }
  }

  cout << answer << endl;

  return 0;
}
