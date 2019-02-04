#include <iostream>
#include <set>
using namespace std;

void main( )
{
    set<int> s;

    s.insert(50);
    s.insert(30);
    s.insert(80);
    s.insert(40);
    s.insert(10);
    s.insert(70);
    s.insert(90);
    
    set<int>::iterator iter;
    for( iter = s.begin() ; iter != s.end() ; ++iter)
        cout << *iter << " ";
    cout << endl;

    pair<set<int>::iterator, set<int>::iterator> iter_pair; //반복자 쌍의 pair 객체

    iter_pair = s.equal_range(30); 
    cout << *iter_pair.first << endl;
    cout << *iter_pair.second << endl;

    iter_pair = s.equal_range(55); 
    if( iter_pair.first != iter_pair.second)
        cout << "55가 s에 있음!" << endl;
    else
        cout << "55가 s에 없음!" << endl;
}