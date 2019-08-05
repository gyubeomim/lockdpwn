/*
  c++ stl p60 함수포인터에 대한 설명 예시 코드
*/

#include <iostream>

using namespace std;

void Print(int n)
{
    cout<<"int: "<< n <<endl;
}



int main()
{
    void (*pf)(int);   // 함수 포인터 선언 
    pf = Print;


    Print(10);
    pf(10);
    (*pf)(10);


    cout<<endl;
        
    
}
