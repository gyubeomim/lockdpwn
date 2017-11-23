/*
	c++ stl  p153 reverse_iterator와 rbegin(), rend() 를 사용한 예제
*/
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> ve;


	ve.push_back(10);
	ve.push_back(20);
	ve.push_back(30);
	ve.push_back(40);
	ve.push_back(50);

	
	
	for (vector<int>::iterator iter = ve.begin(); iter != ve.end(); ++iter)
	{
		cout << *iter << " ";
	}
	cout << endl;



	// reverse_iterator 예제코드
	vector<int>::reverse_iterator riter(ve.rbegin());

	for (; riter != ve.rend(); ++riter)
	{
		cout << *riter << " ";
	}
	cout << endl;


	return 0;



}
























