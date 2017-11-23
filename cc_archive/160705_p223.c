#include <stdio.h>

#define MAX_STRING 100

void printString(int num,FILE *fp);
void printAllString(FILE *fp);

void main()
{
  int num;


  FILE *fp = fopen("character.txt","rb");

  if(fp==NULL)
  {
    puts("파일이 열리지 않습니다");
    return -1;
  }

  printf("출력할 문자열 정보를 입력하세요 (6 이상은 전체 출력): ");
  scanf("%d",&num);

  if(num <= 5)
  {
    printString(num,fp);
  }
  else if (num > 5)
  {
    printAllString(fp);
  }



  fclose(fp);
  puts("출력이 완료되었습니다");


  
}

void printString(int num, FILE *fp)
{
 
  char str[MAX_STRING];

  for(int i=0; i<num-1;i++)
  {
    fgets(str,MAX_STRING-1,fp);
  }

  fgets(str,MAX_STRING-1,fp);
  fputs(str,stdout);

  
}
void printAllString(FILE *fp)
{
  char str[MAX_STRING];

  while(1)
  {
    fgets(str,MAX_STRING-1,fp);

    if(feof(fp) !=0)
      break;

    fputs(str,stdout);
  }
}
