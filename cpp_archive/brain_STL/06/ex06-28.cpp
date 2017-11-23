#include <iostream>
#include <vector>
#include <deque>
using namespace std;

void main() 
{
    vector<int> v(4, 100); //100으로 초기화한 4개의 원소를 갖는 컨테이너 v
    deque<int> dq(4, 100); //100으로 초기화한 4개의 원소를 갖는 컨테이너 dq

    v.push_back( 200 ); // v에 200 추가
    dq.push_back( 200 ); // dq에 200 추가

    for(vector<int>::size_type i = 0 ; i < v.size() ; ++i)
        cout << v[i] << " ";
    cout << endl;
    for(deque<int>::size_type i = 0 ; i < dq.size() ; ++i)
        cout << dq[i] << " ";
    cout << endl;
}
