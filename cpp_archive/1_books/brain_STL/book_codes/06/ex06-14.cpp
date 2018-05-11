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

    for(vector<int>::size_type i = 0 ; i < v.size() ; ++i)
        cout << v[i] << " ";   
    cout << endl;

    v[0] = 100; //범위 점검 없는 0 index 원소의 참조
    v[4] = 500; //범위 점검 없는 4 index 원소의 참조
    for(vector<int>::size_type i = 0 ; i < v.size() ; ++i)
        cout << v[i] << " ";   
    cout << endl;

    v.at(0) = 1000; //범위 점검 있는 0 index 원소의 참조
    v.at(4) = 5000; //범위 점검 있는 4 index 원소의 참조
    for(vector<int>::size_type i = 0 ; i < v.size() ; ++i)
        cout << v.at(i) << " ";   
    cout << endl;
}