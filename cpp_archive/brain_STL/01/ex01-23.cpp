#include <iostream>
using namespace std;

class A
{
};
class B
{
public:
    B( ) { cout << "B() 생성자" << endl; }
    B(A& _a) { cout << "B(A _a) 생성자" << endl; }
    B(int n) { cout << "B(int n) 생성자" << endl; }
    B(double d) { cout << "B(double d) 생성자" << endl; }
};
void main( )
{
    A a;
    int n = 10;
    double d = 5.5;

    B b;   // B() 생성자 호출
    b = a; // b = B(a) 암시적 생성자 호출 후 대입
    b = n; // b = B(n) 암시적 생성자 호출 후 대입
    b = d; // b = B(d) 암시적 생성자 호출 후 대입
}