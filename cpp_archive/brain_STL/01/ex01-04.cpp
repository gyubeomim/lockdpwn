#include <iostream>
using namespace std;

class Point
{
    int x;
    int y;
public:
    Point(int _x =0 , int _y = 0 ):x(_x),y(_y) { }
    void Print( ) { cout << x <<',' << y << endl; }
    void operator+( Point arg)
    {
      cout << "operator+() 함수 호출" << endl;
    }
};
void main( )
{
    Point p1(2,3), p2(5,5);

    p1+p2; // => p1.operator+( p2 ); 와 같습니다.
}