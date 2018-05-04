/*
  열혈 c++ p466  대입 연산자 오버로딩 중 operator[] 에 대한 코드
*/
#include "stdafx.h"
#include <iostream>
#include <cstdlib>

using namespace std;

class Point
{
 private:
  int xpos, ypos;

 public:
  Point(int x = 0, int y = 0) : xpos(x), ypos(y)
  {}

  friend ostream& operator<<(ostream& os, const Point& pos);
};



// cout << ... 
ostream& operator<<(ostream& os, const Point& pos)
{
  os << pos.xpos << ", " << pos.ypos << endl;
  return os;
}





typedef Point* POINT_PTR;





class boundCheckPointPtrArray
{
 private:
  POINT_PTR *arr;
  int arrlen;



  boundCheckPointPtrArray(const boundCheckPointPtrArray& arr)
  {}  // bound 클래스의 복사생성자 (배열의 복사를 원천적으로 막는다)(대부분의 경우 불필요하거나 실수로 간주되므로)
  // private 선언으로 밖에서 접근 못하게 막아놨다
  boundCheckPointPtrArray& operator=(const boundCheckPointPtrArray& arr)
  {} // bound 클래스의 대입연산자 (=)


 public:
  boundCheckPointPtrArray(int len) : arrlen(len)
  {
    arr = new POINT_PTR[len];       // arr.operator[](len)과 같다
  }



  POINT_PTR& operator[](int idx)   // 대입연산자 operator[]
  {
    if (idx < 0 || idx >= arrlen)
    {
      cout << "ERROR OCCURED" << endl;
      exit(1);
    }

    return arr[idx];
  }



  POINT_PTR& operator[](int idx) const  // 대입연산자 operator[] const (함수의 오버로딩을 통해 const형을 받을 때 사용한다)
  {
    if (idx < 0 || idx >= arrlen)
    {
      cout << "ERROR OCCURED" << endl;
      exit(1);
    }

    return arr[idx];
  }


  int getArrayLen() const
  {
    return arrlen;
  }


  ~boundCheckPointPtrArray()
  {
    delete []arr;
  }


};



int main()
{
  boundCheckPointPtrArray eddy(3);

  eddy[0] = new Point(1, 2);      // eddy.operator[] (0)  = new Point(1,2);
  eddy[1] = new Point(100, 200);
  eddy[2] = new Point(10000, 20000);

  for (int i = 0; i < eddy.getArrayLen(); i++)
  {
    cout << *(eddy[i]) << eddy[i] << endl;  // 왜 *를 붙여야하는지 솔직히 잘 모르겠다... 0.0
    // 객체자신을 가르키는 거라고 한다. 그냥 eddy는 주소값인듯
    // eddy.operator[](i)와 같다 arr[idx]를 반환한다
  }

  delete eddy[0];
  delete eddy[1];
  delete eddy[2];

  return 0;

}









