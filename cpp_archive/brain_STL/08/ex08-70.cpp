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
    v.push_back(30);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    vector<int>::iterator iter_lower, iter_upper;

    iter_lower = lower_bound(v.begin(), v.end(), 30);
    iter_upper = upper_bound(v.begin(), v.end(), 30);

    cout<<"30 원소의 순차열 [iter_lower, iter_upper): ";
    for(vector<int>::iterator iter=iter_lower; iter != iter_upper; ++iter)
        cout << *iter << " ";
    cout << endl;
}