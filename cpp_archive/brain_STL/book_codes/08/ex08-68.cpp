#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main( )
{
    vector<int> v;

    v.push_back(10);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);
    v.push_back(20);
        
    cout << "[v 원본]: ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;

    //기본 정렬 기준 less 사용
    sort(v.begin(), v.end());        
    cout << "[v: less 정렬]: ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;

    //비교 조건자 less 지정(일반 버전 binary_search() 가능)
    cout <<"비교 less 찾기: "<< binary_search(v.begin(), v.end(), 20, less<int>()) << endl;

    //정렬 기준 greater 지정
    sort(v.begin(), v.end(), greater<int>());        
    cout << "[v: greater 정렬]: ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;

    //조건자 정렬 기준 greater 지정
    cout <<"비교 greater 찾기: "<< binary_search(v.begin(), v.end(), 20, greater<int>()) << endl;
}