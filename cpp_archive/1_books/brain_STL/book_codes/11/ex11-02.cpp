#include <iostream>
#include <queue>
#include <list>
using namespace std;

void main( )
{
    queue<int, list<int> > q; //리스트를 사용하는 queue 생성

    q.push(10);
    q.push(20);
    q.push(30);

    while( !q.empty() )
    {
        cout << q.front() << endl;
        q.pop();
    }
}