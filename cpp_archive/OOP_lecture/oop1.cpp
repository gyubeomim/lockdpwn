/*
	c++ ==> 객체지향수업, 클래스를 사용해 본 예제 코드
						 생성자, 소멸자 
*/
#include "stdafx.h"
#include <iostream>

using namespace std;

class Circle
{
private:
	int radius;

public:
	double getArea();
	Circle();
	Circle(int r);
	~Circle();
};

Circle::~Circle()
{
	cout << " rad : " << radius << " 's destructor! " << endl;
}

Circle::Circle()
{
	radius = 1;
	cout << "rad : " << radius << endl;
}

Circle::Circle(int r)
{
	radius = r;
	cout << "rad : " << radius << endl;
}

double Circle::getArea()
{
	return 3.14 * radius * radius;
}

int main(int argc, const char *argv[])
{
	Circle donut;
	double area = donut.getArea();
	cout << " donut area : " << area << " cm^2" << endl;

	Circle pizza(30);
	double area2 = pizza.getArea();
	cout << " donut area : " << area2 << " cm^2" << endl;

	return 0;
}
