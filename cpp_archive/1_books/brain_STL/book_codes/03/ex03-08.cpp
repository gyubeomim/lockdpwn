#include <iostream>
#include <functional> //Less<> 헤더
using namespace std;

struct Plus
{
    int operator()(int a, int b)
    {
        return a + b;
    }
};
struct Minus
{
    int operator()(int a, int b)
    {
        return a - b;
    }
};
void main( )
{
    cout << Plus()(10, 20) << endl; //사용자 Plus, Minus 사용
    cout << Plus()(20, 10) << endl;  
    cout << Minus()(10, 20) << endl;
    cout << Minus()(20, 10) << endl; 
    cout << endl;
    cout << plus<int>()(10, 20) << endl; //STL의 plus, minus 사용
    cout << plus<int>()(20, 10) << endl;  
    cout << minus<int>()(10, 20) << endl;
    cout << minus<int>()(20, 10) << endl; 
}