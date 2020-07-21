#include <stdio.h>
#include <string.h>


void main()
{
  char a[20]={0};
  char b[20]={0};
  char c[20]={0};
  char d[20]={0};
  
  char total[80] ={0};

  // 이 부분을 생각못했다... 굳굳
  char * strArr[4] = {a,b,c,d};
  char * strTempPtr;
  int i,j;


  
  for(i=0; i<4;i++)
  {
    printf("문자열 입력 %d : ",i+1);
    scanf("%s",strArr[i]);
  }


  // 포인터로 배열을 바꿔준다 굳굳
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(strcmp(strArr[j], strArr[j+1])>0)
      {
        strTempPtr = strArr[j];
        strArr[j] = strArr[j+1];
        strArr[j+1]=strTempPtr;
      }
    }
  }


  for(i=0;i<4;i++)
  {
    strcat(total,strArr[i]);

    // 한 칸 띄어쓰기를 해줘서 가독성을 높인다
    total[strlen(total)] =' ';
  }


  printf("정렬된 문자열은 :%s\n",total);
  









  
  /*
  for(int i=0; i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
      if(strcmp(a,b)>0)
      {
        strcpy(tmp,a);
        strcpy(a,b);
        strcpy(b,tmp);
      }

      
      
      if(strcmp(a,b)<0 && strcmp(b,c)<0 && strcmp(c,d)<0)
      {
        strcat(total,a);
        strcat(total," ");
        strcat(total,b);
        strcat(total," ");
        strcat(total,c);
        strcat(total," ");
        strcat(total,d);
        strcat(total," ");
      }

      
    }

    
    }
  */




  
}
