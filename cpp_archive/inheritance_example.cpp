#include "stdafx.h"
#include <iostream>

using namespace std;



class edPoint
{
  int x, y;

 public:
  edPoint()
  {
    x = 0;
    y = 0;
  }

  edPoint(int x, int y)
  {
    this->x = x;
    this->y = y;
  }

  int getX()
  {
    return x;
  }


  int getY()
  {
    return y;
  }


 protected:
  void move(int x, int y)
  {
    this->x = x;
    this->y = y;
  }

};


class colorPoint :public edPoint
{
  string color;


 public:
  colorPoint()
  {
    color = "BLACK";
  }

  colorPoint(int x, int y, string color = "BLACK") : edPoint(x, y)
  {
    this->color = color;
  }


  void setPoint(int x, int y)
  {
    move(x, y);
  }


  void setColor(string color)
  {
    this->color = color;
  }

  void show()
  {
    cout << color << "색으로 (" << getX() << "," << getY() << ")에 위치한 점입니다" << endl;
  }





};




int main()
{
  colorPoint zeroPoint;

  zeroPoint.show();


  colorPoint cp(5, 5);

  cp.setPoint(10, 20);
  cp.setColor("BLUE");
  cp.show();


  return 0;

}





