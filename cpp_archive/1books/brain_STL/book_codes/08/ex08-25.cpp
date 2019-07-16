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


    vector<int> v2(5); //size 5인 vector 생성

    vector<int>::iterator iter;
    // 구간 [v1.begin(), v1.end())의 모든 원소를 [v2.begin(), iter)의 순차열로 복사.
    iter = copy(v1.begin(), v1.end(), v2.begin());
    cout <<"v2 마지막 원소: " << *(iter-1) << endl;
    
    cout << "v1 : ";
    for(vector<int>::size_type i = 0; i < v1.size(); ++i)
        cout << v1[i] <<" ";
    cout << endl;
    cout << "v2 : ";
    for(vector<int>::size_type i = 0; i < v2.size(); ++i)
        cout << v2[i] <<" ";
    cout << endl;
}