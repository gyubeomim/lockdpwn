#include <iostream>
using namespace std;

void Print(int n)
{
    cout <<"전역 함수: "<< n << endl;
}
namespace A
{
    void Print(int n)
    {
        cout <<"namespace A 전역 함수: "<< n << endl;
    }
}
class Point
{
public:
    static void Print(int n)
    {
        cout <<"Point 클래스의 정적 멤버 함수: "<< n << endl;
    }
};
void main()
{
    void (*pf)(int );
  
    Print( 10 ); // 1. namespace 없는 전역 함수 호출
    A::Print( 10 ); // 2, namespace A의 전역 함수 호출
    Point::Print( 10 ); // 3, Point 클래스의 정적 멤버 함수 호출
    cout << endl;
        
    pf = Print;
    pf( 10 );  // 1. 함수 포인터로 namespace 없는 전역 함수 호출
    pf = A::Print;
    pf( 10 );  // 2. 함수 포인터로 namespace A의 전역 함수 호출
    pf = Point::Print;
    pf( 10 );  // 3. 함수 포인터로 Point 클래스의 정적 멤버 함수 호출
}