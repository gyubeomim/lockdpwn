#include <iostream>
#include <string>
using namespace std;

void main( )
{
    string t("Hello!");
    const char* p1="Hello!";
    const char* p2=p1+6;

    string s1,s2,s3,s4,s5,s6,s7,s8,s9;

    s1.assign(t);
    s2.assign(t,0,6);    
    s3.assign("Hello!");
    s4.assign("Hello!",6);
    s5.assign(6,'H');
    s6.assign(t.begin(), t.end());
    s7.assign(p1, p2);
    s8 = t;
    s9 = "Hello!";

    //s:string객체, sz:'\0'문자열, c:문자, off:시작위치, n:길이, iter:반복자, p:포인터
    cout <<"s1.assign(s): "<< s1 << endl;
    cout <<"s2.assign(s,off,n): "<< s2 << endl;
    cout <<"s3.assign(sz): "<< s3 << endl;
    cout <<"s4.assign(sz,n): "<< s4 << endl;
    cout <<"s5.append(n, c): "<< s5 << endl;
    cout <<"s6.assign(iter1,iter2): "<< s6 << endl;
    cout <<"s7.assign(p1,p2): "<< s7 << endl;
    cout <<"s8=s: "<< s8 << endl;
    cout <<"s9=sz: "<< s9 << endl;
}