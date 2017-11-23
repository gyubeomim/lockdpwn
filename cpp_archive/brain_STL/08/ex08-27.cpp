#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main( )
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    // 구간 [v.begin(), v.end())의 모든 원소를 0으로 채운다.
    fill(v.begin(), v.end(), 0);
    cout << "v : ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;

    // 구간 [v.begin(), v.begin()+3)의 모든 원소를 55로 채운다.
    fill_n(v.begin(), 3, 55);
    cout << "v : ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;
}