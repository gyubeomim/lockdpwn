#include <stdio.h>


void main()
{
  int num;
  
  
  FILE *fp = fopen("numeric.dat","w");

  if(fp ==NULL)
  {
    puts("파일을 열 수 없습니다");
    return -1;
  }

  for(int i=0; i<5;i++)
  {
    printf("파일에 저장할 숫자 %d ",i+1);
    scanf("%d",&num);
    fprintf(fp,"%d",num);

    
  }

  
  fclose(fp);
  puts("입력이 완료되었습니다");




  
}
