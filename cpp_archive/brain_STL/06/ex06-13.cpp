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

    v.front() = 100; // 첫 번째 원소를 100으로
    v.back() = 500; // 마지막 원소를 500으로
    for(vector<int>::size_type i = 0 ; i < v.size() ; ++i)
        cout << v[i] << " ";   
    cout << endl;
}