#include <stdio.h>


void main()
{
  char c[] = {"가나다라마바사아자차카타파하"};
  
  int i;

  FILE *fp = fopen("character.txt","w");

  if(fp==NULL)
  {
    puts("파일이 열리지 않았습니다");
    return -1;
  }

  for(i=0; i<sizeof(c)-1 ; i++)
  {
    fputc(c[i],fp);
  }

  fclose(fp);
  puts("입력이 안료되었습니다");

  

  
}
