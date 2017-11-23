#include <stdio.h>

#define ARR_LEN 20


int main(){
  int num;
  int binaryArr[ARR_LEN];
  int binaryCnt = 0;


  fputs("10진수 정수 입력: ",stdout);
  scanf("%d",&num);


  printf("%d를 2진수로 변환하면: ",num);

  while(num>0)
  {
    binaryArr[binaryCnt++]=num%2;
    num=num/2;
  }

  while(binaryCnt>0)
  {
    printf("%d",binaryArr[binaryCnt-1]);
    binaryCnt-=1;
  }
  printf("\n");
  
  
}

