/*

 */
#ifndef __HIGHCREDIT_ACCOUNT_H__
#define __HIGHCREDIT_ACCOUNT_H__

#include "NormalAccount.hpp"
#include "String.hpp"


class HighCreditAccount :public NormalAccount
{

 private:
  int specialRate;


 public:

  HighCreditAccount(int ID, int money, String name, int rate, int special)
      : NormalAccount(ID,money, name,rate) , specialRate(special)
  {}

  virtual void Deposit(int money)
  {
    NormalAccount::Deposit(money);
    Account::Deposit(money*(specialRate/100.0));
  }

};

#endif
