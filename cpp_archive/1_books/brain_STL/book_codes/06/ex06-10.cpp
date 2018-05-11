#include <iostream>
#include <vector>
using namespace std;

void main( )
{ 
    vector<int> v(5);

    cout <<"size: "<< v.size() <<"  capacity: " << v.capacity() <<endl;

    vector<int>().swap(v);// 기본 생성자로 만든 vector컨테이너와 v 컨테어너를 swap한다.
    cout <<"size: "<< v.size() <<"  capacity: " << v.capacity() <<endl;
}