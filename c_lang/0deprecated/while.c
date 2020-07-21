/*
 * c ==> 해킹맛보기, 어셈블리용 while문 코드 
 */
#include <stdio.h>

int main(int argc, const char *argv[])
{
  int lv = 0;

  while (1)
  {
    if(lv == 2)
    {
      break;
    }
    printf("%x\n",lv);
    lv++;
  }
	
  return 0;
}
