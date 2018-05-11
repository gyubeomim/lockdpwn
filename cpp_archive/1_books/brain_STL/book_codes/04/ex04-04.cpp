#include <iostream>
using namespace std;

template <typename T>
void Print(T a, T b)
{
    cout << a << ", " << b << endl;
}
void main( )
{
    Print<int>(10, 20); // 정수 출력
    Print<double>(0.123, 1.123); // 실수 출력
    Print<const char*>("ABC", "abcde"); // 문자열 출력
}