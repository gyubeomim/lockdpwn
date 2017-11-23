#include <iostream>
#include <string>
using namespace std;

void main( )
{
    string t("ABC");

    string s1("Hello!");
    string s2("Hello!");
    string s3("Hello!");
    string s4("Hello!");
    string s5("Hello!");
    string s6("Hello!");
    string s7("Hello!");
    string s8("Hello!");
    string s9("Hello!");

    s1.insert(1, "ABC");
    s2.insert(1, "ABC", 2);
    s3.insert(1, t);
    s4.insert(1, t, 0, 2);
    s5.insert(1, 3, 'A');

    s6.insert(s6.begin()+1);
    s7.insert(s7.begin()+1,'A');
    s8.insert(s8.begin()+1, 3, 'A');
    s9.insert(s9.begin()+1, t.begin(), t.end());

    //s:string객체,sz:'\0'문자열,c:문자,pos:삽입위치,positer:삽입반복자,off:위치,n:길이
    cout <<"s1.insert(pos, sz): " << s1 << endl;
    cout <<"s2.insert(pos, sz, n): " << s2 << endl;
    cout <<"s3.insert(pos, s): " << s3 << endl;
    cout <<"s4.insert(pos, s, off, n): " << s4 << endl;
    cout <<"s5.insert(pos, n, c): " << s5 << endl;

    cout <<"s6.insert(positer): " << s6 << endl;
    cout <<"s7.insert(positer, c): " << s7 << endl;
    cout <<"s8.insert(positer, n, c): " << s8 << endl;
    cout <<"s9.insert(positer, iter1, iter2): " << s9 << endl;
}