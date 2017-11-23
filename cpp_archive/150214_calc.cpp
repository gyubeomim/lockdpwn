
#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "math.h"
#include "windows.h"

void calcf(int x, int y, char z);

void main()
{
  char quit = 'y';
  bool isFirstTime = FALSE;

  while (quit == 'y' || quit == 'yes' || quit == 'Y' || quit =='Yes')
  {
    int i = 0;
    int k = 0;
    int j = 0;
    int str[100] = { 0 };
    int str2[100] = { 0 };
    int str3[100] = { 0 };
    char c;
		

    if (isFirstTime == FALSE)     // 사용자가 처음 사용할 때 출력
    {
      printf("Welcome! this is Edward Im's Caculator\n");
      Sleep(1000);
      isFirstTime = TRUE;
    }
    printf("please enter your operaiton : ");
    while ((c = getchar()) != EOF)
    {
      str[i] = c;
      i++;
    }

    for (i = 0; str[i] != 0;)
    {
      if (!isspace(str[i]) && str[i] != '\0')
      {
        str2[j] = str[i];
        j++;
      }
      i++;
    }


    j = 0;  // 변수 초기화


    // 문자열로부터 받은 수를 분해해서 사칙연산 기호 앞에 있는 숫자를 얻는다
    for (i = 0; str2[i] != 0;)
    {

      if (str2[j] == char(43) || str2[j] == char(42) || str2[j] == char(45) || str2[j] == char(47))
      {
        str3[2] = str2[j];

        while (j > 0)
        {
          j--;
          str3[0] += (str2[j] - 48) * (pow(double(10), k));  // 10의 자리가 넘는 수를 계산하기 위해 사용
          k++;
        }
        if (j == 0)
          break;
      }

      j++;
      i++;
    }

    k = 0;   // 변수 초기화


    // 문자열로부터 받은 수를 분해해서 사칙연산 기호 뒤에 있는 숫자를 얻는다
    for (i = 0; str2[i] != 0;)
    {
      i++;
    }

    while (i > 0)
    {
      i--;
      str3[1] += (str2[i] - 48) * (pow(double(10), k));   // 10의 자리가 넘는 수를 계산하기 위해 사용
      if (str2[i - 1] == char(43) || str2[i - 1] == char(42) || str2[i - 1] == char(45) || str2[i - 1] == char(47))
        break;
      k++;
    }


    //계산
    calcf(str3[0], str3[1], str3[2]);
    printf("replay? (press 'y' if you want to replay) (Default (y))");
    quit = getchar();
    if (quit == '\n')
      quit = 'y';
  }
}

void calcf(int x, int y, char z)
{
  if (z == '+')
    printf("%d + %d is %d\n", x, y, x+y);
  else if (z == '*')
    printf("%d * %d is %d\n", x, y, x*y);

  else if (z == '-')
    printf("%d - %d is %d\n", x, y, x-y);

  else if (z == '%')
    printf("%d / %d is %d\n", x, y, x/y);

}

