#include <stdio.h>


void main()
{
  int flag = 0;
  
  printf("1 또는 2를 입력하세요:");

  while(flag == 0){

    scanf("%d",&flag);

    if(flag != 0)
      break;
    else
      printf("숫자를 제대로 입력하세욧");
  }


  // 구구단 알고리즘
  
  if(flag == 1)
  {
    for(int i=3; i<10; i=i+2)
    {
      for(int j=1; j<10;j++)
      {
        printf("%d * %d = %d\n",i,j,i*j);
      }
    }
  }

  if(flag == 2)
  {
    for(int i=2; i<10; i=i+2)
    {
      for(int j=1; j<10;j++)
      {
        printf("%d * %d = %d\n",i,j,i*j);
      }
    }
  }

  


  
}
