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
class PointPtr
{
    Point *ptr;
public:
    PointPtr(Point *p):ptr(p) { }
    ~PointPtr( )
    {
        delete ptr;
    }
};
void main()
{
    PointPtr p1 = new Point(2,3); //메모리 할당
    PointPtr p2 = new Point(5,5); //메모리 할당

    //p1->Print(); // 아직 서비스 사용 못함!
    //p2->Print(); // 아직 서비스 사용 못함!

    //p1의 소멸자에서 Point 동적 객체를 자동 메모리 제거합니다.
    //p2의 소멸자에서 Point 동적 객체를 자동 메모리 제거합니다.
}
