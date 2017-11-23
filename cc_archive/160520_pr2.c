#include <stdio.h>
#include <string.h>
#define MAX_STRING 100


int main(){
  char str1[MAX_STRING];
  char str2[MAX_STRING];
  int i;


  FILE * fp;

  puts("--------------문자열입력및저장-------");

  fp = fopen("string.txt","w");
  fputs("첫번째문자열: ",stdout);
  fgets(str1,MAX_STRING,stdin);

  fwrite(str1, sizeof(char), strlen(str1),fp);

  fputs("두번째문자열: ",stdout);

  fgets(str2,MAX_STRING,stdin);
  fwrite(str2,sizeof(char),strlen(str2),fp);
  puts("");
  fclose(fp);


  puts("----------저장된문자열출력----------");
  fp = fopen("string.txt","r");

  i=0;

  while(1){
    fread(str1+i,sizeof(char),1,fp);

    if(str1[i] == '\n')
    {
      str1[i+1]=0;
      break;
      }
    i++;
   
  }
  
  fprintf(stdout,"첫번째문자열: %s",str1);
  i=0;

  while(1){
    fread(str2+i,sizeof(char),1,fp);
    if(str2[i] == '\n'){
      str2[i+1] = 0;
      break;
      
    }
    i++;
    
  }
  fprintf(stdout,"두번째문자열: %s",str2);
  return 0;
  



}



