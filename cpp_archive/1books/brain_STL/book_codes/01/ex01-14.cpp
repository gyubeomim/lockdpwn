#include <iostream>
using namespace std;


struct FuncObject
{
    
    public:
    
    void operator()( int arg ) const 
    {
        cout <<"정수 : " << arg << endl;
    }
    
};



void Print1( int arg )
{
    cout <<"정수 : " << arg << endl;
}




void main( )
{
    void (*Print2)(int) = Print1;
    FuncObject Print3;

    Print1(10); // 첫째, 함수 호출
    Print2(10); // 둘째, 함수 호출 
    Print3(10); // 첫째, 함수 호출 Print3.operator(10)을 호출
}
