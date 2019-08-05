#include <stdio.h>



void main()
{
  int num =0;
  int a,b,c;

        
  printf("정수를 입력하세요:");
  scanf("%d",&num);

  for(a=0; a<=100; a++){

    for(b=0;b<=100;b++){

      for(c=0;c<=100;c++){

        if((a*b-c) == num)
        {
          printf("%d * %d - %d = %d\n",a,b,c,num);
        }
        
      }
    }
  }




  
}
