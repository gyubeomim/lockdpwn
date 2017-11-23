
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include "String.hpp"

class Account
{
private:
  int accID;
  int balance;
  String cusName;


public:
  Account(int ID, int money = 0 , String Name);

  int GetAccID() const;
  virtual void Deposit(int money);
  int WithDraw(int money);
  void ShowAccInfo() const;

  // ~Account()
  };

#endif
