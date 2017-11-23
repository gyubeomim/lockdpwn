#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main( )
{
    vector<int> v;

    v.push_back(30);
    v.push_back(10);
    v.push_back(20);
    v.push_back(50);
    v.push_back(40);

    vector<int>::iterator iter;
    iter = max_element(v.begin(), v.end());
    cout << *iter << endl;

    iter = min_element(v.begin(), v.end());
    cout << *iter << endl;
}