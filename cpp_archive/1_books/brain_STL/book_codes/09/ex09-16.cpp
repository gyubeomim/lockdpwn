#include <iostream>
#include <functional>
using namespace std;

void main( )
{
    binder2nd< less<int> > binder = bind2nd(less<int>(), 10 );
    unary_negate< binder2nd<less<int> > > negate = not1(binder);

    cout << negate(5) <<':'<< not1(binder)(5) <<':'<< not1( bind2nd(less<int>(), 10) )(5) << endl; //모두 같다.
    cout << negate(10) <<':'<< not1(binder)(10) <<':'<< not1( bind2nd(less<int>(), 10) )(10) << endl;//모두 같다.
    cout << negate(20) <<':'<< not1(binder)(20) <<':'<< not1( bind2nd(less<int>(), 10) )(20) << endl;//모두 같다.
}
