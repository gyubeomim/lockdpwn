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
    string s10("Hello!");

    s1.replace(0, 3, "ABC");
    s2.replace(0, 3, t);
    s3.replace(0, 3, "ABC", 2);
    s4.replace(0, 3, t, 0, 2);

    s5.replace(0, 3, 2, 'A');

    s6.replace(s6.begin(), s6.begin()+3, "ABC");
    s7.replace(s7.begin(), s7.begin()+3, t);
    s8.replace(s8.begin(), s8.begin()+3, "ABC", 2);
    s9.replace(s9.begin(), s9.begin()+3, 3, 'A');
    s10.replace(s10.begin(), s10.end(), t.begin(), t.end());

    //s:string객체,sz:'\0'문자열,c:문자,pos:위치,n:길이,ct:개수,iterb:시작반복자,itere:끝반복자
    cout <<"s1.replace(pos, n, sz): "<< s1 << endl;
    cout <<"s1.replace(pos, n, s): "<< s2 << endl;
    cout <<"s1.replace(pos, n, sz, n2): "<< s3 << endl;
    cout <<"s1.replace(pos, n, s, pos2, n2): "<< s4 << endl;
    cout <<"s1.replace(pos, n, ct, c): "<< s5 << endl;
    cout <<"s1.replace(iterb, itere, sz): "<< s6 << endl;
    cout <<"s1.replace(iterb, itere, s): "<< s7 << endl;
    cout <<"s1.replace(iterb, itere, sz, ct): "<< s8 << endl;
    cout <<"s1.replace(iterb, itere, ct, c): "<< s9 << endl;
    cout <<"s1.replace(iterb, itere, iterb2, itere2): "<< s10 << endl;
}