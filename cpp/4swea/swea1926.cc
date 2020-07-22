#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
  int N;
  cin >> N;

  for(int i=1; i<=N; i++) {
    std::string str = std::to_string(i);

    std::string output;
    for(int i=0; i<str.size(); i++) {
      if(str[i] == '3' || str[i] == '6' || str[i] == '9') {
        output += "-";
      }
    }

    if(output.size() == 0) {
      output = str;
    }

    std::cout << output << " " ;

  }

  return 0;
}
