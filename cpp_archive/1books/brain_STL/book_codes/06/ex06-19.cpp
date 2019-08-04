#include <iostream>
#include <vector>
using namespace std;

void main( )
{ 
    vector<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);

    vector<int>::iterator iter = v.begin();
    vector<int>::const_iterator citer = v.begin();
    
    cout << *iter << endl; //가리키는 원소의 참조
    cout << *citer << endl; //가리키는 원소의 상수 참조

    cout << *++iter << endl; //다음 원소로 이동한 원소의 참조
    cout << *++citer << endl; //다음 원소로 이동한 원소의 상수 참조

    *iter = 100;  // 일반 반복자는 가리키는 원소를 변경할 수 있음.
    //*citer = 100; // 상수 반복자는 가리키는 원소를 변경할 수 없음.
}