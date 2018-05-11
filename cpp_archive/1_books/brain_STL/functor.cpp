/*
	c++ stl p448 functor ==> 함수객체(functor)와 함수 포인터를 사용해본 예제 코드
*/
#include <iostream>

using namespace std;



struct LessFunctor
{
	bool operator() (int left, int right) const  // const를 명시해주면 좋다고 한다
	{
		return left < right;
	}
};



bool LessFun(int left, int right)
{
	return left < right;
}



int main()
{

	bool (*LessPtr)(int, int) = LessFun;  // 함수 포인터 선언
	LessFunctor lessFunctor;  // 함수객체 선언


	cout << lessFunctor(10, 20) << endl;


	cout << LessFun(10, 20) << endl;


	cout << LessPtr(10, 20) << endl;


	return 0;
}






