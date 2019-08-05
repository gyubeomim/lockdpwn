/*
 * c++ ==> OOP수업, 영문자 한 줄을 입력받은 후 거꾸로 출력하는 코드
 */
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
  string str;  // string 클래스 객체를 선언합니다

  while (1) // 무한루프를 돌면서
  {
    cout << "[*] INSERT : ";
    getline(cin, str, '\n');

    if (str == "exit")
    {
      exit(0);
    }
    reverse(str.begin(), str.end());
    cout << "[+] " << str << endl;
  }
  return 0;
}
