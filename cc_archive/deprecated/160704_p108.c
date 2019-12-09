#include <stdio.h>

#define LEN 100

int searchArr(char* arr, char c);


void main()
{
  char string[LEN] = {0};
  char ch;
  int count = 0;

  
  printf("대상 문자열을 입력하세요: ");
  gets(string);

  // 띄어쓰기를 받을 수 없다는 함정.. 큭
  //scanf("%s",string);

  printf("세어 볼 문자를 입력하세요: ");
  ch = getchar();


  count = searchArr(string,ch);

  printf("%c의 개수는 : %d\n",ch,count);

}



int searchArr(char* arr, char c)
{
  int count = 0;

  for(int i=0;i<LEN;i++)
  {
    if(arr[i] == c)
    {
      count++;
    }
    
  }

  return count;
}
