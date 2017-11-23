#include "BankingCommonDecl.hpp"
#include "Account.hpp"

using namespace std;

Account::Account(int ID, int money =0 , String name)
    : accID(ID) , balance(money)
{
  cusName = name;
}

int Account::GetAccID() const
{
  return accID;
}

void Account::Deposit(int money)
{
  balance += money;
}

int Account::Withdraw(int money)
{
  if (balance < money)
  {
    return 0;
  }
  balance -= money;
  return money;
}

void Account::ShowAccInfo() const
{
  cout << "°èÁÂ ID: " << accID << endl;
  cout << "ÀÌ¸§: " << cusName << endl;
  cout << "ÀÜ¾×: " << balance << endl;
}
