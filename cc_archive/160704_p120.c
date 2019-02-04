#include <stdio.h>

// strtoken() 함수 구현

char* StringTokenize(char * str, char *delim);

void main()
{
  char str[] = "111-2222-3333";
  char * delim= "-";
  char * token;

  token = StringTokenize(str,delim);

  while(token!=NULL)
  {
    puts(token);
    token = StringTokenize(NULL,delim);
  }
  
}


char* StringTokenize(char * str, char *delim)
{
  static char* nextTokenPos;
  char * curTokenPos;
  char * curStrPos;


  if(str!=NULL)
  {
    curTokenPos = str;
    curStrPos = str;
    nextTokenPos = (char*)-1;
  }
  else
  {
    curTokenPos = nextTokenPos;
    curStrPos = nextTokenPos;
  }

  if(nextTokenPos==NULL)  // 문자열 끝 도달을 검사한다
    return NULL;

  
 while(1)
 {
   if(*curStrPos ==0) // 문자열의 끝을 검사한다
   {
     nextTokenPos = NULL;
     break;
   }

   if(*curStrPos == delim[0]) // 토큰 구분 문자를 발견한다
   {
     *curStrPos = 0;
     nextTokenPos = curStrPos +1;
     break;
   }

   curStrPos++;
 }

  return curTokenPos;

  
}
