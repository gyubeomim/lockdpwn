/*
	열혈 c++ p435 연산자 opeartor>>(ostream&, const Point&)에 대한 코드
*/

#include "stdafx.h"
#include <iostream>

using namespace std;

class Point
{
private:
	int xpos, ypos;


public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y)
	{	}

	void showPosition() const
	{
		cout << xpos << ", " << ypos << endl;
	}

	friend ostream& operator<<(ostream&, const Point&);
};


ostream& operator<<(ostream& os, const Point& pos)
{
	//	pos.xpos = 1;


	os << pos.xpos << ",,,,, " << pos.ypos << endl;
	return os;
}



int main()
{
	Point pos1(1000, 3000);
	cout << pos1;				// operator<<(cout,pos1) 꼴이 된다


	// cin << pos1;

	Point pos2(1100, 3300);
	cout << pos2;				// operator<<(cout,pos2)


	return 0;
}





















