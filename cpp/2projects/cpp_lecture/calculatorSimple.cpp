/*
 * c++ ==> 객체지향수업, add,sub,mul,div 클래스를 생성해 계산기를 간단하게 구현해본 코드
 */
#include <iostream>
#include <cstdio>
#include <cctype>
#include <cstdlib>

using namespace std;

// Add 클래스 선언
class Add
{
private:
	int a, b;

public:
	void setValue(int x, int y);
	int calculate();
};

// Sub 클래스 선언
class Sub
{
private:
	int a, b;

public:
	void setValue(int x, int y);
	int calculate();
};

// Mul 클래스 선언
class Mul
{
private:
	int a, b;

public:
	void setValue(int x, int y);
	int calculate();
};

// Div 클래스 선언
class Div
{
private:
	int a, b;

public:
	void setValue(int x, int y);
	int calculate();
};

// Add, Sub, Mul, Div의 멤버함수 setValue(), calculate()를 구현한다
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

// 어떤 연산자를 사용했는지 검사하는 함수를 작성한다
int operatorChecker(char op)
{
	if (op == '+' || op == '-' || op == '*' || op == '/')
	{
		return 1;
	}

	return 0;
}

int main(int argc, const char *argv[])
{
	int first, second;
	char op;

	// 각각의 클래스 a,s,m,d를 생성합니다
	Add a;
	Sub s;
	Mul m;
	Div d;

	while (1)
	{
		// 루프를 돌면서 값을 저장한다
		cout << endl;
		cout << "두 정수와 연산자를 입력하세요 >> ";
		cin >> first >> second >> op;

		if (isdigit(first) || isdigit(second))  // 첫번째와 두번째 값이 숫자인지 확인한다
		{
			cout << "다시 해주세요" << endl;
			continue;
		}
		
		if (!operatorChecker(op))  // 3번째 값이 어떤 연산자인지 확인한다
		{
			cout << "다시 해주세요" << endl;
			continue;
		}

		// 확인된 연산자를 사용해 두 숫자의 연산을 수행한다
		switch (op)
		{
		case '+':
			a.setValue(first, second);
			cout << a.calculate();
			break;
		case '-':
			s.setValue(first, second);
			cout << s.calculate();
			break;

		case '*':
			m.setValue(first, second);
			cout << m.calculate();
			break;

		case '/':
			d.setValue(first, second);
			cout << d.calculate();
			break;

		}
	}

	return 0;
}


