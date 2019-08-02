#include <stdio.h>
#include <string.h>

#define LEN 100

void main()
{
  char str[5][LEN] = {0};
  char tmp[LEN] = {0};
  
  printf("문자열 5개를 입력하세요: ");


  // 문자를 입력받고 문자열의 길이를 구한다
  for(int i=0; i<5; i++)
  {
    scanf("%s",str[i]);

    //len[i] = strlen(str[i]);
    // 위 코드는 필요없다
  }

  // 길이를 비교해서 서로 위치를 바꾼다
  for(int k=0; k<4;k++)
  {
    for(int j=0; j<4;j++)
    {
      if(strlen(str[j])>strlen(str[j+1]))
      {
        strcpy(tmp,str[j]);
        strcpy(str[j],str[j+1]);
        strcpy(str[j+1],tmp);
      }
    }
  }

  // 결과를 출력한다
  printf("결과는:");
  for(int w=0;w<5;w++)
  {
    printf("%s %d\n",str[w],w);
  }
}
