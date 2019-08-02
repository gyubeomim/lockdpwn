// c++ stlp 43 스마트 포인터에 대한 코드

#include <iostream>

using namespace std;


class Point
{
  int x;
  int y;


 public:

  Point(int _x = 0, int _y = 0) : x(_x), y(_y)
  {}

  void Print() const
  {
    cout<< x << ',' << y << endl;
  }

    
};


// 스마트 포인터 설정
class PointPtr
{
  Point *ptr;

 public:

  PointPtr(Point *p) : ptr(p)
  {}

  ~PointPtr()
  {
    delete ptr;
  }


  Point* operator->() const
  {
    return ptr;
  }


  Point& operator*() const
  {
    return *ptr;
  }
};




int main()                              
{
  PointPtr p1 = new Point(2,3);
  PointPtr p2 = new Point(5,5);

  p1->Print();                        //  p1.operator->() const 함수를 호출합니다
  p2->Print();                        //  p2.operator->() const 함수를 호출합니다
  //  p1, p2 소멸자에서 자동으로 Point 동적 객체를 메모리에서 해제합니다
  cout<<endl;

    
  Point* p3 = new Point(1,1);
  PointPtr p4 = new Point(2,2);

  p3-> Print();
  p4-> Print();

  cout<<endl;

  (*p3).Print();   // *p3.Print()를 호출합니다
  (*p4).Print();   // p4.operator*().Print() 를 호출합니다

  delete p3;                          // p4는 알아서 소멸됩니다
  return 0;
}
