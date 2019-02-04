#include <stdio.h>

#define MAX_STRING 100
void main()
{
  char *str[5];
  
  int i;

  FILE *fp = fopen("character.txt","w");

  if(fp==NULL)
  {
    puts("파일이 열리지 않았습니다");
    return -1;
  }

  for(i=0; i<5 ; i++)
  {
    printf("%d번째 문자열을 입력하세요 : ",i+1);
    fgets(&str[i],MAX_STRING,stdin);
    fputs(&str[i],fp);
  }

  fclose(fp);
  puts("입력이 완료되었습니다");
  
}
