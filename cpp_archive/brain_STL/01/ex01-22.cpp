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
    Point* operator->()const
    {
        return ptr;
    }
    Point& operator*()const
    {
        return *ptr;
    }
};
void main()
{
    Point* p1 = new Point(2,3); //일반 포인터
    PointPtr p2 = new Point(5,5); //스마트 포인터

    p1->Print(); //p1->Print() 호출 
    p2->Print(); //p2.operator->()->Print() 호출 
    cout << endl;

    (*p1).Print(); //(*p1).Print() 호출
    (*p2).Print(); //p1.operator*().Print() 호출

    delete p1;
    //p2의 소멸자에서 Point 동적 객체를 자동 메모리 제거합니다.
}