// @date:              2020.07.26.Sun
// @level:             D2
// @level:             -
// @description:       1989.
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
  int T;
  cin >> T;

  for(int t=1; t<=T; t++) {
    string sentence;
    cin >> sentence;

    int length = sentence.size();
    bool answer = true;

    if(length % 2 != 1) {
      sentence.insert(sentence.size()/2, "0");
    }

    int n = sentence.size()/2;
    for(int i=1; i<=n; i++) {
      if(sentence.at(n-i) != sentence.at(n+i)) {
        answer=false;
        break;
      }
    }

    cout << '#' << t << ' ' << answer << '\n';

  }

  return 0;
}
