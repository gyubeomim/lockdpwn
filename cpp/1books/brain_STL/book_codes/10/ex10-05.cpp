#include <iostream>
#include <vector>
using namespace std;

void main() 
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    //reverse_iterator 어댑터로 정방향 반복자를 역방향 반복자로 변환
    reverse_iterator<vector<int>::iterator> rbiter(v.end());
    reverse_iterator<vector<int>::iterator> reiter(v.begin());

    cout<<"v [rbiter, reiter) : ";
    for( ; rbiter != reiter ; ++rbiter)
        cout << *rbiter <<" ";
    cout << endl;

    cout<<"v [rbegin(), rend()) : ";
    for(vector<int>::const_reverse_iterator riter=v.rbegin(); riter != v.rend(); ++riter)
        cout << *riter <<" ";
    cout << endl;
}