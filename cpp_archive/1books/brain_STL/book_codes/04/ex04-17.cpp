#include <iostream>
#include <string>
using namespace std;

template <typename IterT, typename Func>
void For_each(IterT begin,IterT end, Func pf )
{
    while( begin != end )
    {
        pf( *begin++ ); 
    }
}
void PrintInt(int data)
{
    cout << data <<" ";
}
void PrintString(string data)
{
    cout << data <<" ";
}
void main( )
{
    int arr[5] = {10, 20, 30, 40, 50};
    For_each(arr, arr+5, PrintInt); // 정수 출력
    cout << endl;

    string sarr[3] = {"abc","ABCDE","Hello!"};
    For_each(sarr, sarr+3, PrintString); // 문자열 출력
    cout << endl;
}

