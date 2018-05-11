#include <iostream>
#include <functional> //Less<> 헤더
using namespace std;

typedef less<int> Less;
void main( )
{
    Less l;

    cout << l(10, 20) << endl; // l 객체로 암시적 함수 호출
    cout << l(20, 10) << endl; // l 객체로 암시적 함수 호출   
    cout << l.operator()(10, 20) << endl;// l 객체로 명시적 함수 호출
    cout << endl;
    cout << Less()(10, 20) << endl; //임시객체로 암시적 함수 호출
    cout << Less()(20, 10) << endl; //임시객체로 암시적 함수 호출   
    cout << Less().operator()(10, 20) << endl;//임시객체로 명시적 함수 호출    
}