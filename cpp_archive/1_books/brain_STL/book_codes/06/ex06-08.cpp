#include <iostream>
#include <vector>
using namespace std;

void main( )
{ 
    vector<int> v(5); //기본값 0으로 초기화된 size가 5인 컨테이너

    v[0] = 10;
    v[1] = 20;
    v[2] = 30;
    v[3] = 40;
    v[4] = 50;
    for(vector<int>::size_type i = 0 ; i < v.size() ; ++i)
        cout << v[i] << " ";   
    cout << endl;
    cout <<"size: "<< v.size() <<"  capacity: " << v.capacity() <<endl;

    v.resize(10); //기본값 0으로 초기화된 size가 10인 컨테이너로 확장
    for(vector<int>::size_type i = 0 ; i < v.size() ; ++i)
        cout << v[i] << " ";   
    cout << endl;
    cout <<"size: "<< v.size() <<"  capacity: " << v.capacity() <<endl;

    v.resize(5); //size가 5인 컨테이너로 축소 capacity는 변화 없음.
    for(vector<int>::size_type i = 0 ; i < v.size() ; ++i)
        cout << v[i] << " ";   
    cout << endl;
    cout <<"size: "<< v.size() <<"  capacity: " << v.capacity() <<endl;
}