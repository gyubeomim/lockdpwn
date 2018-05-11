#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main( )
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    vector<int> v2(5);
    vector<int>::iterator iter_end;
    iter_end = remove_copy(v1.begin(), v1.end(), v2.begin(), 30);

    cout << "v1 : ";
    for(vector<int>::size_type i = 0; i < v1.size(); ++i)
        cout << v1[i] <<" ";
    cout << endl;
    cout << "v2 : ";
    for(vector<int>::size_type i = 0; i < v2.size(); ++i)
        cout << v2[i] <<" ";
    cout << endl;


    cout << "[v2.begin(), iter_end) : ";
    for(vector<int>::iterator iter = v2.begin(); iter != iter_end; ++iter)
        cout << *iter <<" ";
    cout << endl;
}