#include <stdio.h>



int main()
{
  int num;


  FILE *fp = fopen("numeric.dat","rb");

  if(fp==NULL)
  {
    puts("파일이 열리지 않습니다");
    return -1;
  }

  for(int i=0; i<5; i++)
  {
    fread(&num,sizeof(int),1,fp);
    printf("%d 번째 입력된 숫자 : %d \n",i+1,num);
  }

  fclose(fp);
  puts("출력이 완료되었습니다");


  
}
