#include <iostream>
#include <string>
using namespace std;

void main( )
{
    string s("Hello!");
    const char *sz;
    const char *buf;

    sz = s.c_str();
    buf = s.data();

    cout <<"'\\0'문자로 끝나는 문자열(C-style): " << sz << endl;    
    cout <<"'\\0'문자 포함하지 않은 문자열 배열: ";
    for(int i=0 ; i < 6 ; ++i)
        cout << buf[i];
    cout << endl;
}