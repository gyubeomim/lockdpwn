#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
  int T;
  cin >> T;

  while(T--) {
    int N;
    std::string word;
    cin >> N >> word;

    word.erase(N-1,1);

    std::cout << word << std::endl;
  }

  return 0;
}
