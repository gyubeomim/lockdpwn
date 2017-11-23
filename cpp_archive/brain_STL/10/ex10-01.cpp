#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main() 
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    cout<<"v[iterator 읽기 가능] : ";
    for(vector<int>::iterator iter=v.begin(); iter != v.end(); ++iter)
        cout << *iter <<" ";
    cout << endl;

    cout<<"v[const iterator 읽기 가능] : ";
    for(vector<int>::const_iterator citer=v.begin(); citer != v.end(); ++citer)
        cout << *citer <<" ";
    cout << endl;

    vector<int>::iterator iter = v.begin();
    vector<int>::const_iterator citer = v.begin();

    *iter = 100; // 쓰기 가능!
    //*citer = 100; 쓰기 불가능! 에러- 상수 iterator로 가리키는 원소 수정 불가!
}