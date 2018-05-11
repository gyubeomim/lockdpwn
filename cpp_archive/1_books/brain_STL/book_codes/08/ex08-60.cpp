#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void main( )
{
    vector<int> v;
    v.push_back(40);
    v.push_back(10);
    v.push_back(50);
    v.push_back(30);
    v.push_back(20);
    v.push_back(60);

    //부모 노드가 모든 자식 노드보다 작은 힙을 생성한다. 
    make_heap(v.begin(), v.end(), greater<int>());
    cout << "v[힙 생성] : ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;
        
    v.push_back(35);
    push_heap(v.begin(), v.end(), greater<int>());
    cout << "v[힙 추가] : ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;

    sort_heap(v.begin(), v.end(), greater<int>());
    cout << "v[힙 정렬] : ";
    for(vector<int>::size_type i = 0; i < v.size(); ++i)
        cout << v[i] <<" ";
    cout << endl;
}