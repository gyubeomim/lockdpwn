#include <iostream>
using namespace std;

void Print( )
{
    cout <<"정적 함수 Print()"<< endl;
}
class Point
{
public:
    void Print( )
    {
        cout <<"멤버 함수 Print()"<< endl;
    }
};
void main()
{
    Point pt;
    Point * p = &pt;

    Print(); // 첫째, 정적 함수 호출
    pt.Print(); // 둘째, 객체로 멤버함수 호출
    p->Print(); // 셋째, 주소로 멤버함수 호출

}