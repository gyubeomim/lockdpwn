#include <iostream>
#include <deque>
using namespace std;

void main( )
{
    deque<int> dq; 

    dq.push_back(10); 
    dq.push_back(20);
    dq.push_back(30);
    dq.push_back(40);
    dq.push_back(50);

    deque<int>::iterator iter=dq.begin(); //시작 원소를 가리키는 반복자
    cout << iter[0] << endl; // [] 연산자
    cout << iter[1] << endl;
    cout << iter[2] << endl;
    cout << iter[3] << endl;
    cout << iter[4] << endl;
    cout << endl;

    iter += 2; // += 연산
    cout << *iter << endl;
    cout << endl;

    deque<int>::iterator iter2 = iter+2; // + 연산
    cout << *iter2 << endl; 
}