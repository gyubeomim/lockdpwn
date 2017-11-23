#include <iostream>
using namespace std;

class Point
{
    int x; int y;
public:
    explicit Point(int _x =0 , int _y =0 ):x(_x),y(_y) { }
    void Print( ) const { cout << x <<',' << y << endl; }
};

template <typename T>
void Print(T a)
{
    cout << a << endl;
}
void main( )
{
    int n = 10;
    double d = 2.5;
    Point pt(2,3);

    Print( n );
    Print( d );
    Print( pt ); //에러! cout << pt; 연산이 불가능하므로
}