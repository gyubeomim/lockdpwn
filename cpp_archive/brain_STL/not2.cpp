/*
	c++ stl p157 not2 함수 어댑터를 사용햏 less 함수의 역할을 바꾸는 예제 코드
*/
#include <iostream>
#include <functional>


using namespace std;


int main()
{
	cout << less<int>()(10, 20) << endl;
	cout << less<int>()(20, 20) << endl;
	cout << less<int>()(20, 10) << endl;

	cout << "====================================" << endl;
	cout << not2(less<int>())(10, 20) << endl;
	cout << not2(less<int>())(20, 20) << endl;
	cout << not2(less<int>())(20, 10) << endl;



	less<int> le;

	cout << endl<< le(10, 20) << endl;
	cout << le(20, 20) << endl;
	cout << le(20, 10) << endl;

	cout << "====================================" << endl;

	cout << not2(le)(10, 20) << endl;
	cout << not2(le)(20, 20) << endl;
	cout << not2(le)(20, 10) << endl;

	return 0;



}