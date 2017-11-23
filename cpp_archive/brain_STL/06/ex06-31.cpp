#include <iostream>
#include <deque>
using namespace std;

void main( )
{
    deque<int> dq;

    for(int i = 0 ; i < 10 ; i++)
        dq.push_back( (i+1)*10 );

    deque<int>::iterator iter;
    deque<int>::iterator iter2;
    for(iter = dq.begin(); iter != dq.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;


    iter = dq.begin()+2;
    iter2 = dq.insert( iter , 500);
    cout << *iter2 << endl;

    for(iter = dq.begin(); iter != dq.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
}

