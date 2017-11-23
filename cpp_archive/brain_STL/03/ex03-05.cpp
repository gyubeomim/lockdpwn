#include <iostream>
using namespace std;

bool Pred_less(int a, int b)
{
    return a < b;
}
struct Less
{
    bool operator()(int a, int b)
    {
        return a < b;
    }
};
void main( )
{
    Less l;

    cout << Pred_less(10, 20) << endl;
    cout << Pred_less(20, 10) << endl;
    cout << endl;
    cout << l(10, 20) << endl; // l 객체로 암묵적 함수 호출
    cout << l(20, 10) << endl; // l 객체로 암묵적 함수 호출   
    cout << Less()(10, 20) << endl; // 임시객체로 암묵적 함수 호출   
    cout << Less()(20, 10) << endl; // 임시객체로 암묵적 함수 호출   
    cout << endl;
    cout << l.operator()(10, 20) << endl; // 명시적 호출
    cout << Less().operator()(10, 20) << endl; // 명시적 호출
}