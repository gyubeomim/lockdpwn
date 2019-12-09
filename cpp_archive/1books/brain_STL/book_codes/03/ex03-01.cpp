#include <iostream>
using namespace std;
void Print( )
{
    cout << "전역 함수!" << endl;
}
struct Functor
{
    void operator( )( )
    {
        cout << "함수 객체!" << endl;
    }
};
void main( )
{
    Functor functor;

    Print();   // 전역 함수 호출
    functor(); // 멤버 함수 호출 functor.operator()( )와 같다;
}