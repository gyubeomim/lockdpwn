#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

void main( )
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    cout << "v1: ";    
    for(vector<int>::size_type i = 0; i < v1.size(); ++i)
        cout << v1[i] <<" ";
    cout << endl;

    vector<int> v2(5); //size: 5ÀÎ vector »ý¼º
    vector<int>::iterator iter_end;
    iter_end = adjacent_difference(v1.begin(), v1.end(), v2.begin());

    cout << "v2: ";    
    for(vector<int>::size_type i = 0; i < v2.size(); ++i)
        cout << v2[i] <<" ";
    cout << endl;
}
