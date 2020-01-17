#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

void main( )
{ 
    vector<int> v; 
    v.push_back(50); 
    v.push_back(10);
    v.push_back(20);
    v.push_back(40);
    v.push_back(30);

    sort(v.begin(), v.end(), less<int>() ); // 오름차순 정렬
    for(vector<int>::iterator iter= v.begin() ; iter != v.end() ; ++iter)
        cout << *iter << " ";
    cout << endl;

    sort(v.begin(), v.end(), greater<int>() ); // 내림차순 정렬
    for(vector<int>::iterator iter= v.begin() ; iter != v.end() ; ++iter)
        cout << *iter << " ";
    cout << endl;
}