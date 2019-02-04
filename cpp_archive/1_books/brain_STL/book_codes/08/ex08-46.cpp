#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool Pred(int left, int right)
{
    return abs(right-left) < 10;
}
void main( )
{
    vector<int> v;
    v.push_back(10);
    v.push_back(11);
    v.push_back(30);
    v.push_back(32);
    v.push_back(40);
    v.push_back(50);

    cout << "v : ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;

    vector<int>::iterator iter_end;
    iter_end = unique(v.begin(), v.end(), Pred);

    cout << "v : ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;
    cout << "[v.begin(), iter_end) : ";
    for(vector<int>::iterator iter = v.begin(); iter != iter_end; ++iter)
        cout << *iter <<" ";
    cout << endl;
}