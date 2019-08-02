#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool Greater(int left, int right)
{
    return left > right;
}
void main( )
{
    vector<int> v;

    for(int i = 0 ; i < 100 ; ++i)
        v.push_back( rand()%1000 );
    
    cout << "v[정렬 전] : ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;     

    sort(v.begin(), v.end());
    cout << "v[정렬 less] : ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;     

    sort(v.begin(), v.end(), Greater );
    //sort(v.begin(), v.end(), greater<int>() );
    cout << "v[정렬 greater] : ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;     
}