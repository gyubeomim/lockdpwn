/*
	c++ stl p282 map의 [] 연산자를 사용해 원소를 추가하는 예제 코드
*/
#include <iostream>
#include <map>

using namespace std;

int main()
{
	map<int, int> m;

	m[5] = 100;
	m[3] = 100;
	m[8] = 30;
	m[4] = 40;
	m[1] = 70;
	m[7] = 100;
	m[9] = 50;

	map<int, int>::iterator iter;


	for (iter = m.begin(); iter != m.end(); iter++)
	{
		cout << "(" << iter->first << ',' << iter->second << ")" << " ";
	}
	cout << endl;

	
	m[5] = 200;



	for (iter = m.begin(); iter != m.end(); iter++)
	{
		cout << "(" << iter->first << ',' << iter->second << ")" << " ";
	}
	cout << endl;



	return 0;

}
























