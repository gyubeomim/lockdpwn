#include <iostream>
#include <functional>
using namespace std;
void main()
{
    //less의 첫 인자를 10으로 고정한 단항 조건자 binder 생성.
    binder1st< less<int> > binder = bind1st(less<int>(), 10 );

    // binder는 첫 번째 인자를 10으로 고정한 less. 
    cout << binder(5) <<':'<< less<int>()(10, 5) << endl; // 두 문장이 동일합니다.
    cout << binder(10) <<':'<< less<int>()(10, 10) << endl;// 두 문장이 동일합니다.
    cout << binder(20) <<':'<< less<int>()(10, 20) << endl;// 두 문장이 동일합니다.
    cout << "=====위와 같음=====" << endl;
    // 임시 객체 사용
    cout << bind1st(less<int>(), 10 )(5) <<':'<< less<int>()(10, 5) << endl;
    cout << bind1st(less<int>(), 10 )(10) <<':'<< less<int>()(10, 10) << endl;
    cout << bind1st(less<int>(), 10 )(20) <<':'<< less<int>()(10, 20) << endl;   
}