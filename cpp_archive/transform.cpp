/*
	c++ stl p358 algo ==> transform() 알고리즘을 for_each() 알고리즘 대신 사용해본 예제 코드
					// transform() <===> for_each() 알고리즘 모두 모든 객체 원소에 어떠한 변화나 정책을 반영할 때 사용한다
					// transform()은 원본의 순차열 변화없이 목적지의 순차열로 저장한다 (..?)(what..?)
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Func(int n)
{
	return n + 5;
}


int main()
{
	vector<int> v;

	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	v.push_back(50);


	cout << "v : ";
	for (vector<int>::size_type i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
	cout << endl;


	// transform 예제 코드
	transform(v.begin(), v.end(), v.begin(), Func);


	cout << "v : ";
	for (vector<int>::size_type i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
	cout << endl;


	return 0;
}