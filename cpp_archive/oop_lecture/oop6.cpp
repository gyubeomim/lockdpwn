/*
  c++ ==> 객체지향수업, 참조자를 사용해 원의 반지름을 입력해서 넓이를 구하는 예제코드
*/
#include <iostream>

using namespace std;

class Circle
{
  int radius;

 public:
  Circle()
  {
    radius = 1;
  }
  Circle(int radius)
  {
    this->radius = radius;
  }
  void setRadius(int radius)
  {
    this->radius = radius;
  }
  double getArea()
  {
    return 3.14 * radius * radius;
  }
};

void readRadius(Circle &c)
{
  int rad = 0;
  cout << "정수값으로 반지름을 입력하세요 : ";
  cin >> rad;
  c.setRadius(rad);
}

int main(int argc, const char *argv[])
{
  Circle donut;
  readRadius(donut);
  cout << "donut의 면적은 " << donut.getArea() << endl;

  return 0;
}

