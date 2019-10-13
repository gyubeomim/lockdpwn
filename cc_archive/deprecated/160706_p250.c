#include <stdio.h>
#include <string.h>

#define MAX_STRING 100

void main()
{
  char str[MAX_STRING];
  char strPrint[MAX_STRING];
  int i =0;



  printf("-------------문자열 입력---------------\n");
  FILE *fp = fopen("test.txt","w");


  printf("첫 번째 문자열 : ");
  fgets(str,MAX_STRING,stdin);
  fwrite(&str,sizeof(char),strlen(str),fp);
  fflush(stdin);
  
  printf("두 번째 문자열 : ");
  fgets(str,MAX_STRING,stdin);
  fwrite(&str,sizeof(char),strlen(str),fp);
  fflush(stdin);

  fclose(fp);
  
  printf("--------------저장된 문자열 출력---------------\n");

  fp = fopen("test.txt","r");
  
  printf("첫 번째 문자열 출력 : ");
  while(1)
  {
    fread(strPrint+i,sizeof(char),1,fp);

    if(strPrint[i] =='\n')
    {
      strPrint[i+1] = 0;
      break;
    }

    i++;
    
  }
  printf("%s\n",strPrint);

  
  printf("두 번째 문자열 출력 : ");
  i=0;
  while(1)
  {
    fread(strPrint+i,sizeof(char),1,fp);

    if(strPrint[i] =='\n')
    {
      strPrint[i+1] = 0;
      break;
    }

    i++;
    
  }
  printf("%s\n",strPrint);



  fclose(fp);
}
