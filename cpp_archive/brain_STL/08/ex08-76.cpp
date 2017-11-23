#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

void main( )
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    cout << "v: ";    
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;

    cout << accumulate(v.begin(), v.end(), 0) << endl;
    cout << accumulate(v.begin(), v.end(), 100) << endl;
}