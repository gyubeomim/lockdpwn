#include <stdio.h>

int factorial(int num);

void main()
{
  int a=0;
  int result = 0;

  printf("자연수를 입력하세요: ");
  scanf("%d",&a);


  result = factorial(a);

  if(result == 0)
  {
    printf("자연수가 아닌 수를 입력했습니다\n");
    exit(0);
}

  
  printf("%d!은 %d 입니다.\n",a,result);

  
}



int factorial(int num)
{
  int sum = 1;

  if(num <= 0)
    return 0;
  
  for(int i=1; i<=num;i++)
  {
    sum = sum*i;
  }

  return sum;

}
