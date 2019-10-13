#include <stdio.h>


void main()
{
  int a,b;
  int max=0;
  int min=0;
  int sum = 0;
  
  printf("정수 2개를 입력하세요: ");
  scanf("%d %d%",&a,&b);


  max = (a>b)? a:b;
  min = (a>b)? b:a;
 
  for(min;min<=max;min++)
  {
    if((min%3) == 0)
    {
      printf("3의 배수 %d는 제외\n",min);
      continue;
    }
    if((min%5)==0)
    {
      printf("5의 배수 %d는 제외\n",min);
      continue;
    }

    sum = sum + min;
    
  }

  printf("총 합은 %d\n",sum);






  
}
