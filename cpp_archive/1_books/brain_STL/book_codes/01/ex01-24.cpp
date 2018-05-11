#include <iostream>
using namespace std;

class Point
{
    int x;
    int y;
public:
    Point(int _x =0 , int _y =0 ):x(_x),y(_y) { }
    void Print( ) const { cout << x <<',' << y << endl; }
};

void main( )
{
    Point pt;
    pt.Print();

    pt = 10; // Point(10,0) 암시적 생성자 호출
    pt.Print();
}