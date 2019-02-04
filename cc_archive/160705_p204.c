int strLen(char *str)
{
  int len =0;

  while((*str) != 0)
  {
    len++;
    str++;
  }
  
  return len;
  
}


int strCmp(char *str1, char *str2)
{
  while((*str1) !=0 || (*str2) !=0)
  {
    if(*str1>*str2)
    {
      return 1;
    }
    else if(*str1 < *str2)
    {
      return -1;
    }
    else
    {
      str1++;
      str2++;
      continue;
    }


  }
  return 0;
}
