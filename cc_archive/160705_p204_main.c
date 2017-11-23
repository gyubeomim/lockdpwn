#include "myString.h"

void main()
{
  char str1[STR_MAX] = "Good Moring? ";
  char str2[STR_MAX] = "Hello edward, It's nice to meet you bro!";

  char buffString[STR_MAX];

  /* strLen test */
  printf("length of \"%s\" : %d \n", str1, strLen(str1));
  printf("length of \"%s\" : %d \n", str2, strLen(str2));
  

  /* strCpy test */
  strCpy(buffString,str1);
  printf("copy string is : \"%s\" \n", buffString);

  /* strCat test */
  strCat(buffString, str2);
  printf("concat string is : \"%s\" \n", buffString);


  /* strCmp test */
  printf("cmp str1, str1 :%d \n",strCmp(str1,str1));
  printf("cmp str2, str1 :%d \n",strCmp(str2,str1));
  printf("cmp str1, str2 :%d \n",strCmp(str1,str2));
  printf("cmp str2, str2 :%d \n",strCmp(str2,str2));
  
}
