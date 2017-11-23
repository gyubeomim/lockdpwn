#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool Pred(int n)
{
    return 35 < n ;
}
void main( )
{  
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;

    // 구간 [v.begin(), v.end())에서 25 보다 큰 원소의 개수를 반환
    vector<int>::iterator iter;
    iter = find(v.begin(), v.end(), 20);
    if( iter != v.end() )
        cout <<*iter <<"을 찾다!" << endl;

    iter = find_if(v.begin(), v.end(), Pred);
    if( iter != v.end() )
        cout <<"순차열에서 35보다 큰 첫 번째 원소: "<< *iter << endl;
}