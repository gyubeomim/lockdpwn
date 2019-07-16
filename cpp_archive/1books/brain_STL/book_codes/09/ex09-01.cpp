#include <iostream>
using namespace std;

struct LessFunctor // 1. 함수 객체 조건자
{
    bool operator()(int left, int right) const
    {
        return left < right;
    }
};
bool LessFun(int left, int right) // 2. 함수 조건자
{
    return left < right;
}
void main( )
{
    bool (*LessPtr)(int, int) = LessFun; // 3. 함수 포인터 조건자
    LessFunctor lessFunctor;
    
    //모두 bool 형식을 반환
    //1. 함수 객체로 10과 20을 비교
    cout << lessFunctor(10, 20) << endl;

    //2. 함수로 10과 20을 비교
    cout << LessFun(10, 20) << endl;

    //3. 함수 포인터로 10과 20을 비교
    cout << LessPtr(10, 20) << endl;
}
