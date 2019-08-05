/*
 * c++ ==> 객체지향수업, Calc 구현부
 */

#include "calculatorSimple.hpp"

void Add::setValue(int x, int y)
{
	a = x;
	b = y;
}

int Add::calculate()
{
	return a + b;
}

void Sub::setValue(int x, int y)
{
	a = x;
	b = y;
}

int Sub::calculate()
{
	return a - b;
}

void Mul::setValue(int x, int y)
{
	a = x;
	b = y;
}

int Mul::calculate()
{
	return a * b;
}

void Div::setValue(int x, int y)
{
	a = x;
	b = y;
}

int Div::calculate()
{
	return a / b;
}

int operatorChecker(char op)
{
	if (op == '+' || op == '-' || op == '*' || op == '/')
	{
		return 1;
	}

	return 0;
}

