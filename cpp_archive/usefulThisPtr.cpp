#include "stdafx.h"
#include <iostream>

using namespace std;

class TwoNumber {
 private:
  int num1;
  int num2;

 public:
  TwoNumber(int num1, int num2)
  {
    this->num1 = num1;
    this->num2 = num2;
  }


  void ShowTwoNumber()
  {
    cout << this->num1 << endl;
    cout << this->num2 << endl;
  }

};



int main()
{
  TwoNumber two(2, 4);
  two.ShowTwoNumber();
  return 0;



}
