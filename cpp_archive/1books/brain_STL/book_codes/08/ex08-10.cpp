#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool Pred(int left, int right)
{
    return left <= right;
}
void main( )
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(15);
    v1.push_back(20);
    v1.push_back(40);
    v1.push_back(50);
    v1.push_back(60);
    v1.push_back(10);
    v1.push_back(11);
    v1.push_back(12);
    v1.push_back(80);

    vector<int> v2;
    v2.push_back(10);
    v2.push_back(15);
    v2.push_back(25);

    vector<int>::iterator iter;
    iter = find_end(v1.begin(), v1.end(), v2.begin(), v2.end(), Pred);
    if( iter != v1.end() )
    {
        // 일치하는 마지막 순차열의 첫 원소의 반복자 iter
        cout << "iter : " << *iter << endl;
        cout << "iter-1 : " <<*(iter-1) << endl;
        cout << "iter+1 : " <<*(iter+1) << endl;;   
    }
}