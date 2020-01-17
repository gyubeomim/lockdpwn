/*
  c++ ==> 객체지향수업, string 객체를 사용해 여러 수의 덧셈을 해보는 예제 코드
*/
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char *argv[])
{
  string s;
  cout << "7+23+5+100+25 와 같이 덧셈을 입력하세요: " << endl;
  getline(cin, s, '\n');

  int sum = 0;
  int startIndex = 0;

  while (1){
    int fIndex = s.find('+', startIndex);

    if (fIndex == -1){ /// 처음에 '+'를 발견하지 못하면
      string part = s.substr(startIndex);
      if (part == "")
      {
        break;
      }
      cout << part << endl;
      sum += stoi(part);
      break;
    }

    int count = fIndex - startIndex;
    string part = s.substr(startIndex, count);
    cout << part << endl;

    sum += stoi(part);
    startIndex = fIndex + 1;
  }

  cout << "숫자들의 합은: " << sum << endl;
  return 0;
}
