#include <iostream>
using namespace std;

class Point
{
    int x;
    int y;
public:
    Point(int _x =0, int _y =0 ):x(_x),y(_y) { }
    void Print( ) const { cout << x <<',' << y << endl; }
    void operator++ ( ) // 전위 ++
    {
    }
    void operator++(int ) // 후위 ++
    {      
    }
};
void main( )
{
    Point p1(2,3), p2(2,3);

    ++p1; // p1.operator++(); 와 같습니다.

    p2++; // p2.operator++(0); 와 같습니다. 
}

