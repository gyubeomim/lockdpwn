#include <iostream>
#include <set>
using namespace std;

void main( )
{
    set<int, greater<int> > s; // 정렬 기준으로 greater<int> 조건자를 사용.

    s.insert(50);
    s.insert(30);
    s.insert(80);
    s.insert(40);
    s.insert(10);
    s.insert(70);
    s.insert(90);


    // greater<int> 조건자를 사용하는 반복자 생성
    set<int, greater<int> >::iterator iter; 
    for( iter = s.begin() ; iter != s.end() ; ++iter)
        cout << *iter << " ";
    cout << endl;
}