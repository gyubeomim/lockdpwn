#include <stdio.h>

int main()
{
  int n1,n2;
  int add;

  fputs("두 수를 16진수로 입력 : ", stdout);
  scanf("%x %x",&n1,&n2);
  add = n1+n2;


  printf("연산 결과 8진수, 10진수, 16진수 : %o %d %x\n",add,add,add);
  
  return 0;
  
  
}



