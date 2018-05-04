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
    v.push_back(60);

    make_heap(v.begin(), v.end());
    cout << "v[赛 积己] : ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;
        
    pop_heap(v.begin(), v.end());
    cout << "v[赛 昏力] 楷魂 荐青 :";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;
}