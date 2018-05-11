/*
	c++ stl p450 functor ==> transform() 알고리즘을 Plus<int> 함수 객체를 이용해 사용한 예제 코드
*/
#include <iostream>
#include <algorithm>
#include <vector>


using namespace std;

template<typename T>
struct Plus
{
	T operator() (const T& left, const T& right) const
	{
		return left + right;
	}
};


int main()
{

	vector<int> v1;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);


	vector<int> v2;
	v2.push_back(1);
	v2.push_back(2);
	v2.push_back(3);


	vector<int> v3(3);


	// Plus<int> 함수 객체를 사용해 v1 + v2 를 해서 v3에 집어넣는 transform() 알고리즘
	transform(v1.begin(), v1.end(), v2.begin(), v3.begin(), Plus<int>());


	cout << "v1: ";
	for (vector<int>::size_type i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " ";
	}
	cout << endl;


	cout << "v2: ";
	for (vector<int>::size_type i = 0; i < v2.size(); i++)
	{
		cout << v2[i] << " ";
	}
	cout << endl;


	cout << "v3: ";
	for (vector<int>::size_type i = 0; i < v3.size(); i++)
	{
		cout << v3[i] << " ";
	}
	cout << endl;



	return 0;

}





