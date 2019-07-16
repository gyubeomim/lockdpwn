#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

void main( )
{
    vector<int> v1;
    v1.push_back(10); 
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);
    v2.push_back(4);
    v2.push_back(5);

    vector<int> v3(5); //size: 5인 vector 생성

    transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), plus<int>());
    cout <<"v3(v1+v2) : ";
    for(vector<int>::size_type i = 0 ; i < v3.size() ; i++)
        cout << v3[i] << " ";
    cout << endl;

    transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), multiplies<int>());
    cout <<"v3(v1*v2) : ";
    for(vector<int>::size_type i = 0 ; i < v3.size() ; i++)
        cout << v3[i] << " ";
    cout << endl;

    transform(v1.begin(), v1.end(), v3.begin(), negate<int>());
    cout <<"v3(-v1) : ";
    for(vector<int>::size_type i = 0 ; i < v3.size() ; i++)
        cout << v3[i] << " ";
    cout << endl;

    adjacent_difference(v1.begin(), v1.end(), v3.begin(), minus<int>());
    cout <<"v3(v1 인접 원소와의 차) : ";
    for(vector<int>::size_type i = 0 ; i < v3.size() ; i++)
        cout << v3[i] << " ";
    cout << endl;


    partial_sum(v1.begin(), v1.end(), v3.begin(), multiplies<int>());
    cout <<"v3(v1 원소의 곱 누적) : ";
    for(vector<int>::size_type i = 0 ; i < v3.size() ; i++)
        cout << v3[i] << " ";
    cout << endl;

    cout<<"v1 모든 원소의 곱: " << accumulate(v1.begin(), v1.end(), 1, multiplies<int>()) << endl;    
}
