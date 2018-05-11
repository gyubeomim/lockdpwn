#include <iostream>
#include <vector>
using namespace std;

void main( )
{
    vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    for( vector<int>::iterator iter= v.begin(); iter != v.end(); ++iter)
        cout << *iter << " ";
    cout << endl;
    
    // STL 모든 컨테이너는 반복자 어댑터 reverse_iterator를 typedef 타입으로 정의하며
    // rbegin(), rend()로 컨테이너의 역방향 반복자를 반환함.
    vector<int>::reverse_iterator riter(v.rbegin()); 
    for(   ; riter != v.rend() ; ++riter )
        cout << *riter << " ";
    cout << endl;
}