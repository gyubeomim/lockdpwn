#include <iostream>
#include <functional>
using namespace std;

void main( )
{
    less<int> oLess;
    //1. oLess 객체로 10, 20을 비교 true. 암묵적 호출
    cout << oLess(10, 20) << endl;
    //2. oLess 객체로 10, 20을 비교 true.  명시적 호출
    cout << oLess.operator()(10,20) << endl;

    //3. 임시 객체로 10, 20을 비교 true. 암묵적 호출(일반적인 사용)
    cout << less<int>()(10, 20) << endl;
    //4. 임시 객체로 10, 20을 비교 true. 명시적 호출
    cout << less<int>().operator()(10, 20) << endl;
}