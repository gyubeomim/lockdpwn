/*
  Name : main.c ver 1.0
  Content : main function
  Implementation : LKB
  Last modified 2016/07/06
*/
#include "common.h"
#include "screenOut.h"
#include "phoneFunc.h"

enum{INPUT=1, SHOWALL, SEARCH, DELETE ,CHANGE ,QUIT};

int main()
{
  int inputMenu = 0;

  loadDataFromFile();

  while(1)
  {
    ShowMenu();
    scanf("%d",&inputMenu);
    fflush(stdin);

    if(inputMenu >10)
    {
      printf("제대로 된 숫자를 입력해주세요!\n");
      break;
    }

    switch(inputMenu)
    {
      case INPUT:
        InputPhoneData();
        break;

      case SHOWALL:
        ShowAllData();
        break;

      case SEARCH:
        SearchPhoneData();
        break;
        
      case DELETE:
        DeletePhoneData();
        break;
        
      case CHANGE:
        changePhoneData();
        break;
    }

    if(inputMenu == QUIT)
    {
      storeDataToFile();
      puts("이용해 주셔서 고맙소~\n");
      break;
    }
  }

  return 0;
}
/* end of file */
