#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Func(int n)
{
    return n+5;
}
void main( )
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(50);

    vector<int> v2(10); //size: 10 vector 생성

    cout << "v1 : ";
    for(vector<int>::size_type i = 0; i < v1.size(); ++i)
        cout << v1[i] <<" ";
    cout << endl;
    cout << "v2 : ";
    for(vector<int>::size_type i = 0; i < v1.size(); ++i)
        cout << v1[i] <<" ";
    cout << endl;


    vector<int>::iterator iter_end;
    iter_end = transform(v1.begin(), v1.end(), v2.begin(), Func);
    cout << "v1 : ";
    for(vector<int>::size_type i = 0; i < v1.size(); ++i)
        cout << v1[i] <<" ";
    cout << endl;
    cout << "v2 : ";
    for(vector<int>::size_type i = 0; i < v2.size(); ++i)
        cout << v2[i] <<" ";
    cout << endl;
    cout << "[v2.begin(), iter_end) 순차열: " << *v2.begin() <<" ... "<< *(iter_end-1) <<endl;
}