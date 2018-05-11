#include <iostream>
#include <set>
using namespace std;

void main( )
{ 
    multiset<int> ms;
    multiset<int>::iterator iter;    
    
    ms.insert(50);
    ms.insert(30);
    ms.insert(80);
    ms.insert(80); // 80 중복
    ms.insert(30); // 30 중복
    ms.insert(70); 
    iter = ms.insert(10);

    cout << "iter의 원소: " << *iter << endl;

    for( iter = ms.begin() ; iter != ms.end() ; ++iter)
        cout << *iter << " ";
    cout << endl;
}
