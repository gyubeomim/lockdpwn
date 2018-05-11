#include <iostream>
#include <list>
using namespace std;

void main( )
{
    list<int> lt;

    lt.push_back(10);
    lt.push_back(20);
    lt.push_back(30);
    lt.push_back(10);
    lt.push_back(40);
    lt.push_back(50);
    lt.push_back(10);
    lt.push_back(10);
    
    list<int>::iterator iter;    
    for(iter = lt.begin(); iter != lt.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;

    lt.remove(10); // 10 원소의 노드를 모두 제거
    for(iter = lt.begin(); iter != lt.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;
}
