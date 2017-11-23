#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool Pred(int n)
{
    return n <= 30;
}
void main( )
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    v1.push_back(40);
    v1.push_back(30);
    v1.push_back(50);

    vector<int> v2(6); //size: 6인 vector 생성
    vector<int> v3(6); //size: 6인 vector 생성

    cout << "v1 : ";
    for(vector<int>::size_type i = 0; i < v1.size(); ++i)
        cout << v1[i] <<" ";
    cout << endl;
    cout << "v2 : ";
    for(vector<int>::size_type i = 0; i < v2.size(); ++i)
        cout << v2[i] <<" ";
    cout << endl;
    cout << "v3 : ";
    for(vector<int>::size_type i = 0; i < v3.size(); ++i)
        cout << v3[i] <<" ";
    cout << endl;

    vector<int>::iterator iter_end;
    // 30인 원소를 모두 0으로 변환하여 [v2.begin(), iter_end) 순차열에 저장한다.
    iter_end = replace_copy(v1.begin(), v1.end(), v2.begin(), 30, 0);
    // 30이하인 원소를 모두 0으로 변환하여 [v3.begin(), iter_end) 순차열에 저장한다.
    iter_end = replace_copy_if(v1.begin(), v1.end(), v3.begin(), Pred, 0);

    cout << "v1 : ";
    for(vector<int>::size_type i = 0; i < v1.size(); ++i)
        cout << v1[i] <<" ";
    cout << endl;
    cout << "v2 : ";
    for(vector<int>::size_type i = 0; i < v2.size(); ++i)
        cout << v2[i] <<" ";
    cout << endl;
    cout << "v3 : ";
    for(vector<int>::size_type i = 0; i < v3.size(); ++i)
        cout << v3[i] <<" ";
    cout << endl;
}