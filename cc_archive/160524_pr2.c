#include <stdio.h>
#include <unistd.h>

void main()
{
  int a[3];
  int tmp;
  
  
  printf("세 숫자를 입력하세요: ");
  scanf("%d %d %d",&a[0],&a[1],&a[2]);


  while(1){
    
      if(a[0]>a[1]){
        tmp = a[0];
        a[0] = a[1];
        a[1] = tmp;
      }
      
      if(a[1]>a[2]){
        tmp = a[1];
        a[1] = a[2];
        a[2] = tmp;
      }
      printf("%d\n",a[0]);
      printf("%d\n",a[1]);
      printf("%d\n",a[2]);

      sleep(1);
      
      if(a[0] >= a[1] && a[1] >= a[2]){ 
        break;}
      printf("%d\n",a[0]);
      printf("%d\n",a[1]);
      printf("%d\n",a[2]);

      sleep(1);
  }
  
    printf("정렬된 숫자는 %d %d %d\n",a[0],a[1],a[2]);
    
}









