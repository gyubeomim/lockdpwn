/*
	열혈 c++ 상속에 관한 설명 중 유도클래스와 기초클래스에 대한 설명!
*/
#include "stdafx.h"
#include <iostream>


using namespace std;


// 기초 클래스
class SoBase
{
private:
	int baseNum;

public:
	SoBase() : baseNum(123)
	{
		cout << "SoBase()" << endl;
	}


	SoBase(int n) :baseNum(n)
	{
		cout << "SoBase(int n)" << endl;
	}

	void ShowBaseData()
	{
		cout << baseNum << endl;
	}
};


// 유도 클래스
class SoDerived : public SoBase
{
private:
	int derivNum;


public:
	SoDerived() : derivNum(456)
	{
		cout << "SoDeriv()" << endl;
	}


	SoDerived(int n) : derivNum(n)
	{
		cout << "SoDerived(int n)" << endl;
	}


	SoDerived(int n1, int n2) : SoBase(n1), derivNum(n2)
	{
		cout << "SoDerived(int n1,int n2)" << endl;
	}

	void ShowDerivData()
	{
		ShowBaseData();
		cout << derivNum << endl;
	}

};




int main()
{
	cout << "case1..." << endl;
	SoDerived dr1;
	dr1.ShowDerivData();

	cout << "-----------------------------" << endl;
	
	cout << "case2..." << endl;
	SoDerived dr2(12);
	dr2.ShowDerivData();


	cout << "-----------------------------" << endl;

	SoDerived dr3(23, 24);
	dr3.ShowDerivData();
	
	
	return 0;


}
