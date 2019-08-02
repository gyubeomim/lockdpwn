#include <iostream>
#include <string>
using namespace std;

void main( )
{
    string s1("ABCDE");
    string s2("AKABC");
    const char* sz="AKABC";

    //s:string객체, sz:'\0'문자열, off:시작위치, n:길이
    cout <<"s1.compare(s): "<< s1.compare(s2) << endl; 
    cout <<"s1.compare(off,n,s): "<< s1.compare(2,3,s2) << endl; 
    cout <<"s1.compare(off,n,s,off2,n2): "<< s1.compare(0,3,s2,2,3) << endl; 
    cout <<"s1.compare(sz): "<< s1.compare(sz) << endl; 
    cout <<"s1.compare(off,n,sz): "<< s1.compare(2,3,sz) << endl; 
    cout <<"s1.compare(off,n,sz,n2): "<< s1.compare(0,1,sz,1) << endl;
}