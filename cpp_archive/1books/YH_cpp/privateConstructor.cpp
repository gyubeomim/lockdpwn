/*
	열혈 c++ p186 private 생성자, 멤버 이니셜라이저
*/
#include "stdafx.h"
#include <iostream>


using namespace std;



class AAA
{
private:
	int num;

// 생성자 <---> 멤버 이니셜라이저 차이점 알아놓기!
public:
	AAA() : num(0) {}				   // 여기서 :num(0)은 멤버 이니셜라이져
	AAA& CreateInitObj(int n) const
	{
		AAA *ptr = new AAA(n);
		return *ptr;
	}


	void ShowNum() const { cout << num << endl; }


private:
	AAA(int n) : num(n) {}
	
};


int main()
{
	AAA base;
	base.ShowNum();


	AAA &obj1 = base.CreateInitObj(3);
	obj1.ShowNum();

	AAA &obj2 = base.CreateInitObj(12);
	obj2.ShowNum();


	printf("Deleting... \n");

	delete &obj1;
	printf("Complete!\n");

	delete &obj2;
	printf("Complete!\n");

	return 0;
}