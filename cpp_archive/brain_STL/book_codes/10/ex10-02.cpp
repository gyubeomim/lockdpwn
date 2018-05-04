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

    vector<int>::iterator iter = v.begin();
    vector<int>::const_iterator citer = v.begin()+1;
    const vector<int>::iterator const_iter = v.begin()+2;
    const vector<int>::const_iterator const_citer = v.begin()+3;

    //iter는 모두 가능
    *iter = 100; // 가리키는 원소 변경 가능
    ++iter; // 반복자 변경 가능

    //citer
    *citer = 200; // 가리키는 원소 변경 불가능
    ++citer; // 반복자 변경 가능

    //const_iter
    *const_iter = 300; // 가리키는 원소 변경 가능
    ++const_iter; // 반복자 변경 불가능

    //const_citer
    *const_citer = 400; // 가리키는 원소 변경 불가능
    ++const_citer; // 반복자 변경 불가능
}