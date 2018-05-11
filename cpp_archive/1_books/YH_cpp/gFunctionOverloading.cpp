/*
	열혈 c++ p408 연산자 오버로딩 operator+
*/

#include "stdafx.h"
#include <iostream>

using namespace std;

class Point
{
private:
	int xpos, ypos;

public:
	// 함수 인자의 default 값 선언!
	Point(int x = 0, int y = 0) : xpos(x), ypos(y)
	{}


	void showPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}

	friend Point operator+(const Point &pos1, const Point &pos2);

};

// operator 연산자의 첫 사용
Point operator+(const Point &pos1, const Point &pos2)
{
	Point pos(pos1.xpos + pos2.xpos, pos1.ypos + pos2.ypos);
	return pos;
}


int main()
{
	Point pos1(3, 4);
	Point pos2(10,20);

	Point pos3 = pos1 + pos2;

	pos1.showPosition();
	pos2.showPosition();
	pos3.showPosition();

	return 0;
}






