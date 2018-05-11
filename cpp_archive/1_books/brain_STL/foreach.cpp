/*
	c++ stl p342 algo ==> for_each() 알고리즘을 사용해 벡터객체의 크기를 증가시키는 예제 코드
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void Func(int& r)
{
	r += 5;
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
		cout << v[i] << " ";
	}
	cout << endl;


	for_each(v.begin(), v.end(), Func);
	
	
	cout << "v: ";
	for (vector<int>::size_type i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;



	return 0;
}




