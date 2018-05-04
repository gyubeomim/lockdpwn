#include <iostream>
#include <functional> // STL greater와 less 헤더
using namespace std;

template <typename T>
struct Less
{
    bool operator()(T a, T b)
    {
        return a < b;
    }
};
template <typename T>
struct Greater
{
    bool operator()(T a, T b)
    {
        return a > b;
    }
};
void main( )
{
    cout << Less<int>()(10, 20) << endl; //사용자 Less, Greater 사용
    cout << Less<int>()(20, 10) << endl;  
    cout << Greater<int>()(10, 20) << endl;
    cout << Greater<int>()(20, 10) << endl; 
    cout << endl;
    cout << less<int>()(10, 20) << endl; //STL의 less, greater 사용
    cout << less<int>()(20, 10) << endl;  
    cout << greater<int>()(10, 20) << endl;
    cout << greater<int>()(20, 10) << endl; 
}
