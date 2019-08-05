#include "myString.h"



int strCpy(char *dest, char *source)
{
  int len = strLen(source)+1;
  int i;

  for(i=0 ; i<len; i++)
  {
    dest[i] = source[i];
  }


  return len;
}


int strCat(char *dest, char *source)
{
  int destLen = strLen(dest);
  int srcLen = strLen(source)+1;

  int i;


  for(i=0; i<srcLen ;i++)
  {
    dest[destLen+i] = source[i];
  }

  return destLen + srcLen;
  
}
