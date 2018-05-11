/*
	열혈 c++ p428 연산자 오버로딩 중 교환법칙의 성립을 구현한 코드 ex) 3*pos == pos*3 
*/
#include "stdafx.h"
#include <iostream>



using namespace std;


class pointEdward
{
private:
	int xpos, ypos;


public:
	pointEdward(int x = 0, int y = 0) : xpos(x), ypos(y)
	{}

	void showPosition() const
	{
		cout << xpos << "," << ypos << endl;
	}

	pointEdward operator*(int times)
	{
		pointEdward pos(xpos*times, ypos*times);

		return pos;
	}

	friend pointEdward operator*(int times, pointEdward& ref);

};



// 교환법칙 성립을 위해 추가한 코드!   ex) 3*pos == pos*3
pointEdward operator*(int times, pointEdward &ref)
{
	return ref*times;
}


int main()
{
	pointEdward pos(1, 2);
	pointEdward cpy;


	cpy = 3 * pos;
	cpy.showPosition();

	cpy = 2 * pos * 3;
	cpy.showPosition();


	return 0;
}