/*
	열혈 c++ p196
	this 포인터의 이해 
*/
#include "stdafx.h"
#include <iostream>


using namespace std;


class simple
{
private:
	int num;


public:
	simple(int n) : num(n)
	{
		cout << "num = " << num << ", ";
		cout << "address = " << this << endl;
	}


	void ShowSimpleData()
	{
		cout << num << endl;
	}

	simple *GetThisPointer()
	{
		return this;
	}


};



int main()
{
	simple sim1(100);
	simple *ptr1 = sim1.GetThisPointer();

	cout << ptr1 << ", ";
	ptr1->ShowSimpleData();


	simple sim2(200);
	simple *ptr2 = sim2.GetThisPointer();
	
	cout << ptr2 << ", ";
	ptr2->ShowSimpleData();

	return 0;



}