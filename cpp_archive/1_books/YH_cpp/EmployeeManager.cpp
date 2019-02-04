/*
  열혈 c++ p350 상속에서 virtual 함수를 구현한 코드
*/
//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>


using namespace std;

class Employee
{
 private:
  char name[100];

 public:
  Employee(char *name)
  {
    strcpy_s(this->name, 100, name);
  }

  void showYourName() const
  {
    cout << "name: " << name << endl;
  }





  // virtual 함수 정의
  virtual int getPay() const = 0;		// 이와 같이 정의하면 순수 가상함수가 된다.
  // Employee *emp = new Employee("Lee");가 먹히지 않는다
  // Employee를 추상클래스라 부른다1
  virtual void showSalaryInfo() const = 0;


};

class permanentWorker : public Employee
{
 private:
  int salary;


 public:
  permanentWorker(char *name, int money)
      : Employee(name), salary(money)
  {
  }

  int getPay() const
  {
    return salary;
  }

  void showSalaryInfo() const
  {
    showYourName();
    cout << "salary(in permanentWorker class): " << getPay() << endl << endl;
  }



};


class temporaryWorker :public Employee
{
 private:
  int workTime;
  int payPerHour;

 public:
  temporaryWorker(char *name, int pay)
      :Employee(name), workTime(0), payPerHour(pay)
  {}


  void addWorkTime(int time)
  {
    workTime += time;
  }

  int getPay() const
  {
    return workTime * payPerHour;
  }

  void showSalaryInfo() const
  {
    showYourName();
    cout << "salary(in tmpWorker class):  " << getPay() << endl << endl;

  }

};


class salesWorker :public permanentWorker
{
 private:
  int saleResult;
  double bonusRatio;

 public:
  salesWorker(char *name, int money, double ratio)
      : permanentWorker(name, money), saleResult(0), bonusRatio(ratio)
  {}


  void addSalesResult(int value)
  {
    saleResult += value;
  }

  int getPay() const
  {
    // 함수 오버라이딩 (function overridding)
    return permanentWorker::getPay() + (int)(saleResult * bonusRatio);
  }

  void showSalaryInfo() const
  {
    showYourName();
    cout << "salary(in salesWorker class):  " << getPay() << endl << endl;

  }

};



class employeeHandler
{
 private:
  Employee* empList[50];
  int empNum;


 public:
  employeeHandler() : empNum(0)
  {}


  void addEmployee(Employee *emp)
  {
    empList[empNum++] = emp;
  }





  // virtual 함수의 사용. 원래는 아래에 두 for문은 사용이 안되지만 virtual 함수를 통해 구현할 수 있다
  void showAllSalaryInfo() const
  {
    for (int i = 0; i < empNum; i++)
    {
      empList[i]->showSalaryInfo();
    }
  }

  void showTotalSalary() const
  {
    int sum = 0;

    for (int i = 0; i < empNum; i++)
    {
      sum += empList[i]->getPay();
    }

    cout << "salary sum: " << sum << endl;

  }


  ~employeeHandler()
  {
    for (int i = 0; i < empNum; i++)
    {
      delete empList[i];
    }
  }

};



int main()
{
  employeeHandler handler;

  handler.addEmployee(new permanentWorker("Kim", 1000));
  handler.addEmployee(new permanentWorker("Lim", 1500));
	

  temporaryWorker *alba = new temporaryWorker("Jung알바", 700);
  alba->addWorkTime(5);
  handler.addEmployee(alba);



  salesWorker *seller = new salesWorker("Hong세일즈맨", 1000, 0.1);
  seller->addSalesResult(7000);
  handler.addEmployee(seller);

  handler.showAllSalaryInfo();


  handler.showTotalSalary();

  return 0;



}
