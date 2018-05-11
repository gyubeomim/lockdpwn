#include <iostream>
using namespace std;

template <typename T1, typename T2>
void Print(T1 a, T2 b)
{
    cout << a << ", " << b << endl;
}
void main( )
{
    Print(10, 1.5); // 정수, 실수 출력
    Print("Hello!", 100); // 문자열, 정수 출력
    Print(1.5, "Hello!"); // 실수, 문자열 출력
}