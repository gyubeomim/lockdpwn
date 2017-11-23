/*
  c++ stl p48 타입변환 연산자 오버로딩에 관한 코드
*/

#include <iostream>

using namespace std;

class A
{};



class B
{
    public:

    B()
    {
        cout<< "B()"<<endl;;
        
    }

    B(A& _a)
    {
        cout<< "B(A& _a)"<<endl;
    }


    B(int n)
    {
        cout<< "B(int n)"<<endl;
    }

    B(double d)
    {
        cout<< "B(double d)"<<endl;
    }
    
};


int main()
{
    A a;

    int n = 10;
    double d = 5.5;

    B b;   // b() 호출

    b = a;   // b(A& _a) 호출 
    b = n;   // b(int n) 호출
    b = d;   // b(double d) 호출

    return 0;

    
}
