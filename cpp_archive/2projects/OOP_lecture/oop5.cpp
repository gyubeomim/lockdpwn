/*
  c++ ==> 객체지향수업, string 클래스를 사용해 여러 문장에서 특정 문자열을 바꿔보는 코드
*/
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char *argv[])
{
  string s;
	
  cout << "여러줄의 문자열을 입력하세요 입력의 끝은 &입니다" << endl;
  getline(cin, s, '&');
  cin.ignore();

  string f,r;
  cout << endl << "find: ";
  getline(cin, f, '\n');
  cout << endl << "replace: ";
  getline(cin, r, '\n');

  int startIndex = 0;
  while(1) {
    int fIndex = s.find(f, startIndex);
		
    if(fIndex == -1) {
      break;
    }
		
    s.replace(fIndex, f.length(), r);
    startIndex += fIndex + r.length();
  }
	
  cout << s << endl;
  return 0;
}

