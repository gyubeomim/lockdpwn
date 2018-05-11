#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool Pred(int left, int right)
{
    return left > right;
}
void main( )
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    vector<int> v2;
    v2.push_back(40);
    v2.push_back(80);
    v2.push_back(20);

    cout << "v1 : ";
    for(vector<int>::size_type i = 0; i < v1.size(); ++i)
        cout << v1[i] <<" ";
    cout << endl;
    cout << "v2 : ";
    for(vector<int>::size_type i = 0; i < v2.size(); ++i)
        cout << v2[i] <<" ";
    cout << endl;

    vector<int>::iterator iter;
    iter = find_first_of(v1.begin(), v1.end(), v2.begin(), v2.end(), Pred);
    if( iter != v1.end() )
        cout << "iter : " << *iter << endl;
}