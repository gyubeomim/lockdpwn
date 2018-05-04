#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//이항 조건자
bool Pred(int a, int b)
{
    return abs(b-a) > 10;
}
void main( )
{  
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(50);
    v.push_back(90);

    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;

    vector<int>::iterator iter; 
    iter = adjacent_find(v.begin(), v.end(), Pred);

    if( iter != v.end() )
        cout << *iter << endl;

    for( ; iter != v.end() ; ++iter)
        cout << *iter <<" ";
    cout << endl;
}