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
    //가능~!
    cout<<"30이상 40이하가 아닌 원소 개수: " << count_if(v.begin(), v.end(), not1( ptr_fun(Pred) ) ) << endl;    
}