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
        cout << v[i] << endl;   

    cout << typeid(vector<int>::size_type).name() << endl;
}