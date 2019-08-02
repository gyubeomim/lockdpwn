
#include "BankingCommonDecl.hpp"
#include "Account.hpp"

using namespace std;


// 생성자 (계좌 생성)
Account::Account(int ID, int money , String name)
    : accID(ID) , balance(money)
{
  cusName = name;
}


// ID 확인
int Account::GetAccID() const
{
  return accID;
}


// 입금
void Account::Deposit(int money)
{
  balance += money;
}


// 출금
int Account::Withdraw(int money)
{
  if (balance < money)
  {
    return 0;
  }

  balance -= money;
  return money;
}


// 계좌정보출력
void Account::ShowAccInfo() const
{
  cout << "계좌 ID: " << accID << endl;
  cout << "이름: " << cusName << endl;
  cout << "잔액: " << balance << endl;
}
