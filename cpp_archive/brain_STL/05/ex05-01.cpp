#include <iostream>
#include <vector>
using namespace std;

void main( )
{
    vector<int> v; // 정수를 저장하는 컨테이너 v 생성

    v.push_back(10); // v에 정수 추가
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    for(unsigned int i = 0 ; i < v.size() ; ++i)
        cout << v[i] << endl; // v[i]는 i번째 index의 정수 반환
}