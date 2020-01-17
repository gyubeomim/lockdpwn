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

    vector<int>::iterator iter;
    vector<int>::iterator iter2;
    for( iter = v.begin(); iter != v.end() ; ++iter)
        cout << *iter << " ";
    cout << endl;

    iter = v.begin()+2;
    // iter가 가리키는 위치의 원소를 제거합니다. iter2는 다음 원소 40
    iter2 = v.erase(iter); 

    for( iter = v.begin(); iter != v.end() ; ++iter)
        cout << *iter << " ";
    cout << endl;

    // [v.begin()+1, v.end()) 구간의 원소를 제거합니다.   
    iter2 = v.erase(v.begin()+1, v.end()); // iter2는 다음 원소 v.end()

    for( iter = v.begin(); iter != v.end() ; ++iter)
        cout << *iter << " ";
    cout << endl;
}
