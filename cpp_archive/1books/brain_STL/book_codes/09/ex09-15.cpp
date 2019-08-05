#include <iostream>
#include <functional>
using namespace std;

void main( )
{
    less<int> oLess;
    binary_negate< less<int> > negate= not2(less<int>());

    cout << negate(5, 10) <<':'<< not2(oLess)(5, 10) <<':'<< not2( less<int>() )(5, 10) << endl; //모두 같다.
    cout << negate(10, 10) <<':'<< not2(oLess)(10, 10) <<':'<< not2( less<int>() )(10, 10) << endl; //모두 같다.
    cout << negate(20, 10) <<':'<< not2(oLess)(20, 10) <<':'<< not2( less<int>() )(20, 10) << endl; //모두 같다.
}
