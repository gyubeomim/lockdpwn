/*
  banking system Ver 0.1
  Implementation : Edward Im
  160717
*/

#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;
const int NAME_LEN = 20;

void ShowMenu();
void MakeAccount();
void DepositMoney();
void WithdrawMoney();
void ShowAllAccInfo();                  // 잔액조회


enum{MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT};

typedef struct
{
     int accID;
     int balance;
     char cusName[NAME_LEN];
     
} Account;


Account accArr[100];


int main()
{
     int choice;

     while(1)
     {
          ShowMenu();
          cout<<"선택: ";
          cin>>choice;
          cout<<endl;

          switch(choice)
          {
          case MAKE:
               MakeAccount();
               break;
          case DEPOSIT:
               DepositMoney();
               break;
          case WITHDRAW:
               WithdrawMoney();
               break;
          case INQUIRE:
               ShowAllAccInfo();
               break;
          case EXIT:
               return 0;
          default:
               cout<<"Illegal selection.."<<endl;
          }
               
     }
     return 0;
}



void ShowMenu()
{

     
}

void MakeAccount()
{
     
}
void DepositMoney()
{
     
}
void WithdrawMoney()
{
     
}
void ShowAllAccInfo()
{
     
}
