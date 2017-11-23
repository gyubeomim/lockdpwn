#include <stdio.h>

// 정수 n을 입력받아 블라블라~
void main()
{
  int a = 0 ;
  int i = 0 ;
  int sum = 0 ;


  printf("정수를 입력하세요: ");
  scanf("%d",&a);

  for(i=0; i<=a ; i++)
  {
    sum = sum +i;
  }

  printf("정답은 %d 입니다\n",sum);
  


  
}
