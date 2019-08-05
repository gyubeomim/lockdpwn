#include <iostream>
#include <string>
using namespace std;

void main( )
{
    string s1, s2;

    
    //cin >> buf와 같다.
    //cout << "두 문자열 입력:"<<endl;
    //cin >> s1 >> s2;
    //cout <<"s1: "<< s1 <<"   s2: "<< s2 << endl;

    //cin.getline(buf)과 같다.
    cout << "두 문자열 입력(공백 문자 가능):"<<endl;
    getline(cin, s1);
    getline(cin, s2, '\n');
    cout <<"s1: "<< s1 <<endl;
    cout <<"s2: "<< s2 << endl;
}