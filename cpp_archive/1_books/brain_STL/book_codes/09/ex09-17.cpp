#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

bool Pred(int n)
{
    return 30 <= n && n <= 40;
}
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

    cout<<"30이상 40이하의 원소 개수: " << count_if(v.begin(), v.end(), Pred) << endl;    
    //다음은 에러입니다. not1은 어댑터로 함수 객체에 argument_type, result_type가 정의되어 있어야 함!
    cout<<"30이상 40이하가 아닌 원소 개수: " << count_if(v.begin(), v.end(), not1(Pred) ) << endl;    
}