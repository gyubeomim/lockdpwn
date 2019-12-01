#include <iostream>
#include "BankingCommonDecl.hpp"
#include "AccountHandler.hpp"

using namespace std;

int main()
{
  AccountHandler manager;
  int choice;

  while (1)
  {
    manager.ShowMenu();
    cout << "¼±ÅÃ: ";
    cin >> choice;
    cout << endl;

    switch (choice)
    {
      case MAKE:
        manager.MakeAccount();
        break;

      case DEPOSIT:
        manager.DepositMoney();
        break;

      case WITHDRAW:
        manager.WithdrawMoney();
        break;

      case INQUIRE:
        manager.ShowAllAccInfo();
        break;

      case EXIT:
        return 0;

      default:
        cout << "Illegal selection " << endl;
    }
  }
  return 0;
}
