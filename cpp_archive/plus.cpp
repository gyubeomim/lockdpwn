/*
	c++ stl p456 functor ==> plus<int>를 사용한 예제 코드
*/
#include <iostream>
#include <functional>

using namespace std;

int main()
{
	plus<int> oPlus;

	// plus<int> 함수 객체를 사용한 예제 코드
	cout << oPlus(10, 20) << endl;
	cout << oPlus.operator()(10, 20) << endl;
	cout << plus<int>()(10, 20) << endl;
	cout << plus<int>().operator()(10, 20) << endl;

	return 0;
}
