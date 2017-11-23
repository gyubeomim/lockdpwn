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

    v.push_back(20);
    v.push_back(30);
    v.push_back(60);

    cout << "v의 두 구간으로 정렬된 하나의 순차열"<<endl;
    cout << "[v.begin(), v.begin()+5) + [v.begin()+5, v.end())"<<endl;
    cout << "v: ";    
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;


    // 두 구간으로 정렬된 하나의 순차열을 한 구간으로 정렬한다.
    inplace_merge(v.begin(), v.begin()+5, v.end());

    cout << "v: ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;
}