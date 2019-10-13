/*
	열혈 c++ p454 생성자, 복사생성자, 대입연산자이 어떻게 사용되는지 보여주는 코드
*/
#include "stdafx.h"
#include <iostream>


using namespace std;


class AAA
{
private:
	int num;

public:
	AAA(int n = 0) :num(n)		// 생성자
	{
		cout << "AAA(int n =0) CALLED" << endl;
	}

	AAA(const AAA& ref) : num(ref.num)			// 복사 생성자
	{
		cout << "AAA(const AAA& ref) CALLED" << endl;
	}

	AAA& operator=(const AAA& ref)		// 대입연산자
	{
		num = ref.num;
		cout << "operator= CALLED" << endl;
		return *this;
	}
};


class BBB
{
private:
	AAA edward;

public:
	BBB(const AAA& ref) : edward(ref)
	{}

};


class CCC
{
private:
	AAA edward2;

public:

	// AAA& ref를 먼저 생성시키고 operator= 로  입력되는 메커니즘인듯
	CCC(const AAA& ref)
	{
		edward2 = ref;
	}
};


int main()
{
	AAA obj1(12);

	cout << "********************************" << endl;;

	BBB obj2(obj1);

	cout << "********************************" << endl;

	CCC obj3(obj1);

	return 0;
}