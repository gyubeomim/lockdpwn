#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

///////////////////////server////////////////////////
//객체의 멤버 함수를 호출할 수 있는 함수 객체 클래스
template <typename RType, typename CType>
class Mem_fun_class: public unary_function<CType, RType>
{
    RType (CType::*pf)() const;
public :
    Mem_fun_class( RType (CType::*_pf)() const ):pf(_pf) {}
    RType operator()(const CType* p ) const
    {      
         return (p->*pf)();
    }
};
// 어댑터 함수 : 멤버 함수를 주소를 저장하는 함수 객체를 반환
template <typename RType, typename CType>
Mem_fun_class<RType, CType> Mem_fun( RType (CType::*pf) () const )
{
    return Mem_fun_class<RType,CType>( pf );
}
////////////////////////client/////////////////////////////
class Point
{
    int x;
    int y;
public:
    explicit Point(int _x =0 , int _y =0 ):x(_x),y(_y) { }
    void Print( ) const { cout << x <<',' << y << endl; }
    int GetX() const { return x; }
    int GetY() const { return y; }
};
void main() 
{
    vector<Point*> v;
    v.push_back( new Point(1,1) );
    v.push_back( new Point(2,2) );
    v.push_back( new Point(3,3) );
    v.push_back( new Point(4,4) );
    v.push_back( new Point(5,5) );

    //STL 버전
    for_each(v.begin(), v.end(), mem_fun(&Point::Print) );
    //사용자 버전
    for_each(v.begin(), v.end(), Mem_fun(&Point::Print) );
    // 객체 delete 생략
}