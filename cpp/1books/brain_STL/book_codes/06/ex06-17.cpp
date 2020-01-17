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

    for(vector<int>::iterator iter = v.begin(); iter != v.end() ; ++iter)
        cout << *iter << " ";   
    cout << endl;
}