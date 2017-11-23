#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<typename T>
struct Plus
{
    T operator( )(const T& left, const T& right) const
    {
        return left + right;
    }
};
void main( )
{
    vector<int> v1;
    v1.push_back(10); 
    v1.push_back(20);
    v1.push_back(30);

    vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);

    vector<int> v3(3); //size: 3인 vector 생성

    //STL 조건자 plus<int> 사용
    //transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), plus<int>());
    //사용자 정의 조건자 Plus<int> 사용
    transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), Plus<int>());

    cout <<"v1 : ";
    for(vector<int>::size_type i = 0 ; i < v1.size() ; i++)
        cout << v1[i] << " ";
    cout << endl;

    cout <<"v2 : ";
    for(vector<int>::size_type i = 0 ; i < v2.size() ; i++)
        cout << v2[i] << " ";
    cout << endl;

    cout <<"v3 : ";
    for(vector<int>::size_type i = 0 ; i < v3.size() ; i++)
        cout << v3[i] << " ";
    cout << endl;
}

