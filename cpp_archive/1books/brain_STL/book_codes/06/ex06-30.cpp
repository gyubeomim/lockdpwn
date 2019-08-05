#include <iostream>
#include <deque>
using namespace std;

void main() 
{
    deque<int> dq;

    dq.push_back( 10 );
    dq.push_back( 20 );
    dq.push_back( 30 );
    dq.push_back( 40 );
    dq.push_back( 50 );

    deque<int>::iterator iter;
    for(iter = dq.begin(); iter != dq.end() ; ++iter)
        cout << *iter << " ";
    cout << endl;

    iter = dq.begin()+2; //반복자에 +2합니다.
    cout << *iter << endl;

    iter += 2; //반복자에 +2합니다.
    cout << *iter << endl;

    iter -= 3; //반복자에 -3합니다.
    cout << *iter << endl;
}
