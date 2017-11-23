#include <iostream>
using namespace std;

class A
{
};
class B
{
public:
    operator A( )
    {
        cout << "operator A() 호출" << endl;
        return A();
    }
    operator int( )
    {
        cout << "operator int() 호출" << endl;
        return 10;
    }
    operator double( )
    {
        cout << "operator double() 호출" << endl;
        return 5.5;
    }
};
void main( )
{
    A a;
    int n;
    double d;

    B b;
    a = b; //b.operator A() 암시적 호출
    n = b; //b.operator int() 암시적 호출
    d = b; //b.operator double() 암시적 호출

    cout << endl;
    a = b.operator A(); // 명시적 호출
    n = b.operator int(); // 명시적 호출
    d = b.operator double(); // 명시적 호출
}