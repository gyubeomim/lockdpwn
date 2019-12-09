#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void main( )
{
    vector<int> v;
    v.push_back(10); 
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    cout <<"v : ";
    for(vector<int>::size_type i = 0 ; i < v.size() ; i++)
        cout << v[i] << " ";
    cout << endl;

    cout <<"20 보다 작은 원소의 개수: "<< count_if(v.begin(), v.end(), 
        bind2nd<less<int> >(less<int>(), 20) ) << endl;
    cout <<"20 보다 작거나 같은 원소의 개수: "<< count_if(v.begin(), v.end(), 
        bind2nd<less_equal<int> >(less_equal<int>(), 20) ) << endl;
    cout <<"20 보다 큰 원소의 개수: "<< count_if(v.begin(), v.end(), 
        bind2nd<greater<int> >(greater<int>(), 20) ) << endl;
    cout <<"20 보다 크거나 같은 원소의 개수: "<< count_if(v.begin(), v.end(), 
        bind2nd<greater_equal<int> >(greater_equal<int>(), 20) ) << endl;
    cout <<"20과 같은 원소의 개수: "<< count_if(v.begin(), v.end(), 
        bind2nd<equal_to<int> >(equal_to<int>(), 20) ) << endl;
    cout <<"20과 다른 원소의 개수: "<< count_if(v.begin(), v.end(), 
        bind2nd<not_equal_to<int> >(not_equal_to<int>(), 20) ) << endl;
}
