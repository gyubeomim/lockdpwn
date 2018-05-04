#include <iostream>

using namespace std;

class Point
{
  int x;
  int y;

 public:

  explicit Point(int _x= 0, int _y = 0) : x(_x), y(_y)
  {}


  void Print() const
  {
    cout<<x <<', '<<y <<endl;
  }

  void PrintInt(int n)
  {
    cout<<"테스트 정수: "<<n <<endl;
  }

};


int main()
{
  Point pt(2,3);
  Point *p = &pt;

    
  void (Point::*pf1)() const;
  pf1 = &Point::Print;

  void (Point::*ppp)() const;
  ppp = pf1;
    
  void (Point::*pf2)(int);
  pf2 = &Point::PrintInt;

  void (Point::*fff)(int);
  fff = pf2;
    
    
  pt.Print();
  pt.PrintInt(1);

  p->Print();
  p->PrintInt(2);

    
  (pt.*pf1)();
  (pt.*pf2)(3);

  (pt.*ppp)();
  (pt.*fff)(4);
    
  cout<<endl;

   
}

