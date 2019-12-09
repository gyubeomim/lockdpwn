/*
  c++ ==> 객체지향수업, 클래스를 사용해 본 예제 코드2
*/
#include "stdafx.h"
#include <iostream>

using namespace std;

class Rectangle
{
 private:
  int width;
  int height;

 public:
  Rectangle();
  Rectangle(int a);
  Rectangle(int a, int b);
	
  double getArea();
  bool isSquare();
};

Rectangle::Rectangle()
{
  width = 1;
  height = 1;
}

Rectangle::Rectangle(int a)
{
  width = a;
  height = a;
}

Rectangle::Rectangle(int a, int b)
{
  width = a;
  height = b;
}

bool Rectangle::isSquare()
{
  if (width == height)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

double Rectangle::getArea()
{
  return width * height;
}

int main()
{
  Rectangle rect1;
  Rectangle rect2(3);
  Rectangle rect3(3,5);

  if (rect1.isSquare())
  {
    cout << "rect1 is a Square" << endl;
  }
  if (rect2.isSquare())
  {
    cout << "rect2 is a Square" << endl;
  }
  if (rect3.isSquare())
  {
    cout << "rect3 is a Square" << endl;
  }

  return 0;
}
