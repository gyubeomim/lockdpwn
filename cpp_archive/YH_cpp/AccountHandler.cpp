#include "BankingCommonDecl.hpp"
#include "AccountHandler.hpp"
#include "Account.hpp"
#include "NormalAccount.hpp"
#include "HighCreditAccount.hpp"
#include "String.hpp"

using namespace std;

// 생성자
AccountHandler::AccountHandler()
    : accNum(0)
{}

// ATM 메뉴
void AccountHandler::ShowMenu(void) const
{
  cout << "-----------MENU---------" << endl;
  cout << "1. 계좌 개설" << endl;
  cout << "2. 입금" << endl;
  cout << "3. 출금" << endl;
  cout << "4. 계좌정보 전체 출력" << endl;
  cout << "5. 프로그램 종료" << endl;
}

// 계좌만들기
void AccountHandler::MakeAccount()
{
  int sel;

  cout << "[계좌 종류 선택]" << endl;
  cout << "1. 보통 예금 계좌" << endl;
  cout << "2. 신용 신뢰 계좌" << endl;

  cout << "당신의 선택은 : ";
  cin >> sel;

  if (sel == NORMAL)
  {
    MakeNormalAccount();
  }
  else if(sel == CREDIT)
  {
    MakeCreditAccount();
  }
  else
  {
    cout << "ERROR!";
    return ;
  }
}

// 보통예금계좌 개설
void AccountHandler::MakeNormalAccount()
{
  int id;

  String name;
  int balance;
  int interRate;

  cout << "[보통예금계좌 개설]" << endl;

  cout << "계좌 ID: ";
  cin >> id;

  cout << "이름: ";
  cin >> name;

  cout << "입금액: ";
  cin >> balance;

  cout << "이자율: ";
  cin >> interRate;
  cout << endl;

  accArr[accNum++] = new NormalAccount(id, balance, name, interRate);
}

// 신용신뢰계좌 개설
void AccountHandler::MakeCreditAccount()
{
  int id;
  String name;
  int balance;
  int interRate;
  int creditLevel;

  cout <<"[신용신뢰계좌 개설]"<<endl;

  cout << "계좌 ID: ";
  cin >> id;

  cout << "이름: ";
  cin >> name;

  cout << "입금액: ";
  cin >> balance;

  cout << "이자율: ";
  cin >> interRate;

  cout << "신용등급(1toA, 2toB, 3toC): ";
  cin >> creditLevel;

  cout << endl;

  switch (creditLevel)
  {
    case 1:
      accArr[accNum++] = new HighCreditAccount(id,balance,name,interRate,LEVEL_A);
      break;

    case 2:
     accArr[accNum++] = new HighCreditAccount(id,balance,name,interRate,LEVEL_B);
      break;

    case 3:
     accArr[accNum++] = new HighCreditAccount(id,balance,name,interRate,LEVEL_C);
      break;
  }
}

// 입금
void AccountHandler::DepositMoney()
{
  int money;
  int id;

  cout << "[입 금]" << endl;

  cout << "계좌 ID: ";
  cin >> id;

  cout << "입금액: ";
  cin >> money;

  for (int i= 0; i<accNum; i++)
  {
    if(accArr[i]->GetAccID() == id)
    {
      accArr[i]->Deposit(money);
      cout << "[+] 입금 완료되었습니다" << endl << endl;
      return ;
    }
  }
  cout << "[-] 유효하지 않은 ID입니다." << endl << endl;
}

// 출금
void AccountHandler::WithdrawMoney()
{
  int money;
  int id;

  cout << "[출 금]" << endl;

  cout << "계좌 ID: ";
  cin >> id;

  cout << "입금액: ";
  cin >> money;

  for (int i= 0; i<accNum; i++)
  {
    if(accArr[i]->GetAccID() == id)
    {
      if (accArr[i]->Withdraw(money) == 0)
      {
        cout << "[-] 잔액이 부족합니다" << endl << endl;
        return ;
      }
      cout << "[+] 출금이 완료됐습니다" << endl << endl;
      return ;
    }
  }
  cout << "[-] 유효하지 않은 ID입니다." << endl << endl;
}

// 계좌정보 출력
void AccountHandler::ShowAllAccInfo() const
{
  for (int i = 0; i< accNum; i++)
  {
    accArr[i]->ShowAccInfo();
    cout << endl;
  }
}




// 소멸자
AccountHandler::~AccountHandler()
{
  for (int i =0; i < accNum; i++)
  {
    delete accArr[i];
  }

}



