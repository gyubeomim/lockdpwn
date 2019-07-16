#include <iostream>
using namespace std;
void For_each(int *begin, int *end, void (*pf)(int ) )
{
    while( begin != end )
    {
        pf( *begin++ ); 
    }
}
void PrintInt(int n)
{
    cout << n <<" ";
}
void main( )
{
    int arr[5] = {10, 20, 30, 40, 50};
    For_each(arr, arr+5, PrintInt); // 정수 출력
    cout << endl;
}

