/*
	c++ ==> 객체지향수업, 포인터를 사용해 Circle의 면적을 구해보는 코드
*/
#include <iostream>

using namespace std;

class Circle
{
private:
	int radius;

public:
	double getArea();
	void setRadius(int r);
};

void Circle::setRadius(int r)
{
	radius = r;
}

double Circle::getArea()
{
	return 3.14 * radius * radius;
}


int main(int argc, const char *argv[])
{
	Circle circleArray[3];

	circleArray[0].setRadius(10);
	circleArray[1].setRadius(20);
	circleArray[2].setRadius(30);


	for (int i = 0; i < 3; i++)
	{
		cout << "Circle " << i << " 의 면적은 " << circleArray[i].getArea() << endl;
	}

	cout << endl;
	
	Circle *p;
	p = circleArray;

	for (int i = 0; i < 3; i++)
	{
		cout << "Circle " << i << " 의 면적은 " << p->getArea() << endl;
		p++;
	}

	return 0;
}



