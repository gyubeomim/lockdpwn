/*
  열혈 c++ p606 예외클래스와 예외객체에 관한 코드 throw (DepositException)
  그리고 AccountException으로 예외처리를 상속관계로 해놓으면 훨씬 사용하기 좋다
*/
#include "stdafx.h"
#include <iostream>
#include <cstring>


using namespace std;


class AccountException
{
 public:
  virtual void showExceptionReason() = 0; // 순수 가상함수를 선언해서 예외처리를 상속으로 해결하게 한다
};


class DepositException   : public AccountException
{
 private:
  int reqDep;

 public:
  DepositException(int money) : reqDep(money)
  {}


  void showExceptionReason()
  {
    cout << "Exception: " << reqDep << endl;
  }

};


class WithdrawExcpetion  : public AccountException
{
 private:
  int balance;

 public:
  WithdrawExcpetion(int money) :balance(money)
  {}

  void showExceptionReason()
  {
    cout << "Exception2: " << balance << endl;
  }

};


class Account
{
 private:
  char accNum[50];
  int balance;

 public:
  Account(char *acc, int money) : balance(money)
  {
    int len = strlen(acc) + 1;
    strcpy_s(accNum, len, acc);
  }



  void Deposit(int money) throw (AccountException)  // throw (DepositException)은 없어도 동작한다
  {													// 명시하기 위해 쓰는듯
    if (money < 0)
    {
      DepositException expn(money);
      throw expn;
    }
		
    balance += money;

  }

  void Withdraw(int money) throw (AccountException)
  {
    if (money > balance)
    {
      throw WithdrawExcpetion(balance);
    }

    balance -= money;
  }

  void ShowMyMoney()
  {
    cout << "잔고: " << balance << endl << endl;
  }

};


int main()
{
  Account myAcc("56345-2342", 5000);

  try
  {
    myAcc.Deposit(2000);
    myAcc.Deposit(-300);
  }

  catch (AccountException &expn)
  {
    expn.showExceptionReason();
  }

  myAcc.ShowMyMoney();
  try
  {
    myAcc.Withdraw(3500);
    myAcc.Withdraw(5000);

  }
  catch (AccountException &expn)
  {
    expn.showExceptionReason();
  }
  myAcc.ShowMyMoney();

  return 0;
}












