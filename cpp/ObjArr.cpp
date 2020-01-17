#include "stdafx.h"
#include <iostream>

using namespace std;

class Person
{
 private:
  char *name;
  int age;

 public:
  // 보통 생성자
  Person(char *myname, int myage)
  {
    int len = strlen(myname) + 1;
    name = new char[len];

    strcpy_s(name,100, myname);
    age = myage;
  }

  // void 형 생성자
  Person()
  {
    name = NULL;
    age = 0;
    cout << "called Person()" << endl;
  }

  void SetPersonInfo(char *myname, int myage)
  {
    name = myname;
    age = myage;
  }

  void ShowPersonInfo() const
  {
    cout << "Name: " << name << ", ";
    cout << "Age: " << age << endl;
  }

  ~Person()
  {
    delete []name;
    cout << "called Destructor!" << endl;
  }
};


int main()
{
  Person parr[1];
  char namestr[100];
  char *strptr;
  int age;
  int len;

  for (int i = 0; i < 1; i++)
  {
    cout << "Name: ";
    cin >> namestr;
    cout << "Age: ";
    cin >> age;

    len = strlen(namestr) + 1;
    strptr = new char[len];

    strcpy_s(strptr,100, namestr);
    parr[i].SetPersonInfo(strptr, age);

  }

  parr[0].ShowPersonInfo();
  //	parr[1].ShowPersonInfo();
  //parr[2].ShowPersonInfo();
}







