/*
	c++ stl p454 functor ==> adaptor를 적용한 transform() 함수 사용법에 관한 예제 코드
							// :public binary_function<> 을 사용해 쉽게 사용할 수 있다
*/
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T>
struct Plus
{
	typedef T first_argument_type;
	typedef T second_argument_type;
	typedef T result_type;

	T operator()(const T& left, const T& right) const
	{
		return left + right;
	}

};



template<typename T>
struct Plus2 : public binary_function<T,T,T>   // binary_function<>을 사용해 쉽게 Plus 대신 사용할 수 있다 
{

	T operator()(const T& left, const T& right) const
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

	vector<int> v3(3);

	vector<int> v6(3);




	transform(v1.begin(), v1.end(), v3.begin(), binder1st<Plus<int>>(Plus<int>(), 100));

	// : public binary_function<T,T,T>를 사용해 훨씬 쉽게 binder1st<>를 사용할 수 있다
	transform(v1.begin(), v1.end(), v6.begin(), binder1st<Plus2<int>>(Plus2<int>(), 100));



	cout << "v1: ";
	for (vector<int>::size_type i = 0; i < v1.size(); i++)
	{
		cout << v1[i] << " ";
	}
	cout << endl;


	cout << "v3: ";
	for (vector<int>::size_type i = 0; i < v3.size(); i++)
	{
		cout << v3[i] << " ";
	}
	cout << endl;



	cout << "v6: ";
	for (vector<int>::size_type i = 0; i < v6.size(); i++)
	{
		cout << v6[i] << " ";
	}
	cout << endl;



	return 0;
}

