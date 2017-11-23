#include <iostream>
using namespace std;

class Point
{
    int x; int y;
public:
    explicit Point(int _x =0 , int _y =0 ):x(_x),y(_y) { }
    void Print( ) const { cout << x <<',' << y << endl; }
};
// 일반화 함수 템플릿
template <typename T>
void Print(T a)
{
    cout << a << endl;
}
// 특수화 함수 템플릿
template < >
void Print(Point a) // 명시적인 코드: void Print<Point>(Point a)
{
    cout << "Print 특수화 버전: ";
    a.Print();
}
void main( )
{
    int n = 10;
    double d = 2.5;
    Point pt(2,3);

    Print( n );  // Print<int>( n )    일반화 버전 호출
    Print( d );  // Print<double>( d ) 일반화 버전 호출
    Print( pt ); // Print<Point>( pt ) 특수화 버전 호출
}