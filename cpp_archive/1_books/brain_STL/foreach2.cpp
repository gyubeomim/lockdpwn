/*
	c++ stl p343 algo ==> for_each() 알고리즘과 Accumulation 클래스를 사용해
						  벡터객체의 원소를 계속해서 더하는 예제
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Accumulation
{
	int total;


public:
	
	explicit Accumulation(int init = 0) : total(init)
	{}


	void operator() (int& r)
	{
		total += r;
		r = total;
	}

};


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



	for_each(v.begin(), v.end(), Accumulation(0));
	cout << "v : ";
	for (vector<int>::size_type i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;



	for_each(v.begin(), v.end(), Accumulation(1));
	cout << "v : ";
	for (vector<int>::size_type i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;



	for_each(v.begin(), v.end(), Accumulation(1));
	cout << "v : ";
	for (vector<int>::size_type i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;



	for_each(v.begin(), v.end(), Accumulation(1));
	cout << "v : ";
	for (vector<int>::size_type i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;


	return 0;
}




