
#ifndef __ACCOUNT_HANDLER_H__
#define __ACCOUNT_HANDLER_H__

#include "Account.hpp"
#include "AccountArray.hpp"

class AccountHandler
{

 private:

  BoundCheckAccountPtrArray accArr;
  int accNum;



 public:

  AccountHandler();
  void ShowMenu(void) const;
  void MakeAccount();
  void DepositMoney();
  void WithdrawMoney();
  void ShowAllAccInfo() const;
  ~AccountHandler();



 protected:
  void MakeNormalAccount();
  void MakeCreditAccount();


};

#endif
