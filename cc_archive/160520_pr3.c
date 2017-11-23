#include <stdio.h>
#include <string.h>

#define MAX_STRING 100
#define READ_CNT 100

int main()
{
  int readCnt;


  char src[MAX_STRING];
  char dest[MAX_STRING];
  char dataBuff[READ_CNT];


  FILE * fp_src;
  FILE * fp_dest;

  fputs("원본이름: ",stdout);
  gets(src);


  fputs("복사된이름: ",stdout);
  gets(dest);

  fp_src = fopen(src,"rb");
  if (fp_src ==NULL)
    puts("원본파일을열지못했습니다");

  fp_dest = fopen(dest,"wb");
  if (fp_dest ==NULL)
    puts("복사본을생성하지못했습니다");

  while(1)
  {
    readCnt = fread(dataBuff, 1 ,READ_CNT,fp_src);
  }
  
    
  


}
