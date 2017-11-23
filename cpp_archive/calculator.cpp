#include "stdafx.h"
#include <iostream>

using namespace std;

class calc
{
	int a, b;

public:
	void setValue(int x, int y);
	int add();
	int sub();
	int mul();
	double div();

};

void calc::setValue(int x, int y)
{
	a = x;
	b = y;
}

int calc::add()
{
	return a + b;
}

int calc::sub()
{
	return a - b;
}

int calc::mul()
{
	return a*b;
}

double calc::div()
{
	return a / b;
}

// MAIN START
int main()
{
	int x, y;
	char c;

	calc cal;

	cout << "두 정수의 연산자는: ";
	cin >> x >> c >> y;

	cal.setValue(x, y);

	switch (c)
	{
	case '+':
		cout << cal.add();
		break;

	case '-':
		cout << cal.sub();
		break;

	case '*':
		cout << cal.mul();
		break;

	case '/':
		cout << cal.div();
		break;

	default:
		break;
	}

	cout << endl;

	return 0;
}








