#include <iostream>
#include <list>
using namespace std;

void main( )
{
    list<int> lt;

    lt.push_back(10);
    lt.push_back(20);
    lt.push_back(30);
    lt.push_back(40);
    lt.push_back(50);
    
    list<int>::iterator iter = lt.begin();
    list<int>::iterator iter2;
    ++iter;
    ++iter; 

    iter2 = lt.erase(iter); //iter(30)의 원소를 제거합니다.

    for(iter = lt.begin(); iter != lt.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;

    cout << "iter2 : " << *iter2 << endl;

    iter = iter2;
    iter2 = lt.insert(iter, 300); //iter2(40)이 가리키는 위치에 300을 삽입합니다.
    for(iter = lt.begin(); iter != lt.end(); ++iter)
        cout << *iter << ' ';
    cout << endl;

    cout << "iter2 : " << *iter2 << endl;
}
