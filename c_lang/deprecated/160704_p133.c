#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define EXT_SIZE 5

int ExtendMemForString(char **pStr, int strLen);


void main()
{
  int strLen = 5;
  char *str = (char*)malloc(sizeof(char)*strLen);

  strcpy(str,"Best");
  puts(str);


  strLen = ExtendMemForString(&str,strLen);
  printf("확장된 문자열 길이 : %d \n",strLen);
  strcat(str, " guy");
  puts(str);
    
}


//adf asdf
int ExtendMemForString(char **pStr, int strLen)
{
  int i;
  char *newStrPtr;

  newStrPtr = (char*)malloc(sizeof(char)*(strLen+EXT_SIZE));

  if(newStrPtr==NULL)
    return -1;
  
  for(i=0; i<strLen; i++)
    newStrPtr[i] = (*pStr)[i];
   

  free(*pStr);
  *pStr = newStrPtr;
  
  return strLen + EXT_SIZE;
  
}
