#include <stdio.h>


void main()
{
  int a[5] = {0};
  int tmp =0 ;
  
  printf("5개의 정수를 입력하세요: ");
  scanf("%d %d %d %d %d",&a[0],&a[1],&a[2],&a[3],&a[4]);


  //버블 알고리즘
  
    for(int i=0;i<4;i++)
    {
      for(int j=0;j<4;j++)
      {
        if(a[j]>a[j+1])
        {
          tmp = a[j];
          a[j] = a[j+1];
          a[j+1] = tmp;
        }
      }
    }



    printf("%d %d %d %d %d\n",a[0],a[1],a[2],a[3],a[4]);




  
}
