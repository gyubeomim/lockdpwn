#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//출력 매개 변수로 사용하기 위해 &(레퍼런스)를 사용함!!!
void Func(int& r)
{
    r += 5;
}
void main( )
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    cout << "v : ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;


    for_each(v.begin(), v.end(), Func);
    cout << "v : ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;
}