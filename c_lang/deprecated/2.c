#include <stdio.h>
#include <string.h>

#define MAX_LEN 5


void main()
{
  int studentScore[MAX_LEN] = {0};
  int count = 0;
  int tmp= 0 ;

  
  printf("학번과 성적을 성적순으로 정렬하는 프로그램입니다.\n");

  
  while(1)
  {
    printf("학번과 성적을 차례로 입력해주세요 [%d] [종료: ctrl + D] : ",count+1);
    scanf("%d",&studentScore[count]);

    
    if (count == 4)
      break;

    count++;
  }

  
  for(int i = 0 ; i < count ; i++)
  {
    for(int j =0; j < count ; j++)
    {
      if(studentScore[j] > studentScore[j+1])
      {
        tmp = studentScore[j];
        studentScore[j] = studentScore[j+1];
        studentScore[j+1] = tmp;
      }
    }
  }


  printf("오름차순으로 정렬된 성적은 다음과 같습니다\n");
  
  for(int i = 0;  i <= count ; i++)
  {
    printf("학번 : [%d], 성적 : [%d]\n",i+1,studentScore[i]);
  }
  
}


