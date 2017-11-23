#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100


// 구조체를 선언합니다
typedef struct student
{
  char name[MAX_LEN];
  int mathScore;
  int koreanScore;
  int englishScore;
  int totalScore;
  double meanScore;
} STUDENT;


enum{NAME=1, SCOREHIGH, SCORELOW, QUIT};

STUDENT student[MAX_LEN];
STUDENT tmp;

// 학생들의 점수를 구하는 함수
void getStudentScore(int num);

// 총점을 구하는 함수
void getTotalScore(int num);

// 평균을 구하는 함수
void getMeanScore(int num);

// 정렬하는 함수들
void sortStudentByScoreHigh(int num);
void sortStudentByScoreLow(int num);
void sortStudentByScoreName(int num);



void main()
{
  int maxNum;
  int selection = 0;
  char a[MAX_LEN];
  
  // 초기화면을 지웁니다
  system("clear");

  
  
  printf("한 반의 최대 학생수를 정하세요: ");
  scanf("%d",&maxNum);

  printf("%lf,%d",maxNum,maxNum);

  
  // 코드 추가
  if(maxNum == 0)
  {
    puts("잘못된 입력입니다. 프로그램을 종료합니다...");
    exit(0);
  }

  printf("\n[%d]명의 학생 정보를 입력하세요\n",maxNum);

  // 학생 정보를 입력하고 총점, 평균을 구합니다

  for(int i = 0 ; i< maxNum ; i++)
  {
    getStudentScore(i);
    getTotalScore(i);
    getMeanScore(i);

    printf("\n");
  }

  // 입력된 정보를 정렬 후 출력합니다
  while(1)
  {
    printf("\n1. 이름순으로 출력\n2. 성적(오름차순)으로 출력\n3. 성적순(내림차순)으로 출력\n4. 프로그램 종료\n");
    printf("어떤 순으로 출력하시겠습니까?: ");
    scanf("%d",&selection);
  
    if(selection > 0 && selection < 5)
    {
      switch(selection)
      {
        case NAME:
          sortStudentByScoreName(maxNum);
          continue;
          
        case SCOREHIGH:
          sortStudentByScoreHigh(maxNum);
          continue;
          
        case SCORELOW:
          sortStudentByScoreLow(maxNum);
          continue;
          
        case QUIT:
          printf("[-] 프로그램을 종료합니다...\n");
          exit(0);
      }
    }
    else
      continue;
    
  }
  
  
}

// 학생들의 점수를 구하는 함수
void getStudentScore(int num)
{
  printf("이름 : ");
  scanf("%s",student[num].name);

  printf("국어 : ");
  scanf("%d",&student[num].koreanScore);
  
  printf("영어 : ");
  scanf("%d",&student[num].englishScore);
  
  printf("수학 : ");
  scanf("%d",&student[num].mathScore);
  
}


// 총점을 구하는 함수
void getTotalScore(int num)
{
  student[num].totalScore = student[num].englishScore + student[num].koreanScore + student[num].mathScore;
}


// 평균을 구하는 함수
void getMeanScore(int num)
{
  student[num].meanScore = student[num].totalScore / 3;
}




// 오름차순으로 정렬
void sortStudentByScoreHigh(int num)
{
  
  
  for(int i = 0; i< num-1 ; i++)
  {
    for(int j = 0; j < num-1 ; j++)
    {
      if(student[j].totalScore > student[j+1].totalScore)
      {
        tmp = student[j];
        student[j] = student[j+1];
        student[j+1] = tmp;
      }
    }
  }

  printf("\n<성적표>\n");
  printf("이름      국어    영어    수학    총점    평균\n");
  
  for(int i = 0; i <num;i++)
  {
    printf("%s       %d       %d       %d       %d      %.1lf\n",student[i].name, student[i].koreanScore, student[i].englishScore, student[i].mathScore, student[i].totalScore, student[i].meanScore);
  }
  
}

// 내림차순으로 정렬
void sortStudentByScoreLow(int num)
{

  
  for(int i = 0; i< num-1 ; i++)
  {
    for(int j = 0; j < num-1 ; j++)
    {
      if(student[j].totalScore < student[j+1].totalScore)
      {
        tmp = student[j];
        student[j] = student[j+1];
        student[j+1] = tmp;
      }
    }
  }

  printf("\n<성적표>\n");
  printf("이름      국어    영어    수학    총점    평균\n");
  
  for(int i = 0; i <num;i++)
  {
    printf("%s       %d       %d       %d       %d      %.1lf\n",student[i].name, student[i].koreanScore, student[i].englishScore, student[i].mathScore, student[i].totalScore, student[i].meanScore);
  }
  
}

// 이름 순으로 정렬
void sortStudentByScoreName(int num)
{
 
  
  for(int i = 0; i< num-1 ; i++)
  {
    for(int j = 0; j < num-1; j++)
    {
      if(strcmp(student[j].name,student[j+1].name) > 0)
      {
        tmp = student[j];
        student[j] = student[j+1];
        student[j+1] = tmp;
      }
    }
  }

  printf("\n<성적표>\n");
  printf("이름      국어    영어    수학    총점    평균\n");
  
  for(int i = 0; i <num;i++)
  {
    printf("%s       %d       %d       %d       %d      %.1lf\n",student[i].name, student[i].koreanScore, student[i].englishScore, student[i].mathScore, student[i].totalScore, student[i].meanScore);
  }
  
}
