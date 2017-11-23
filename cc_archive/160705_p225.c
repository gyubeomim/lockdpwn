#include <stdio.h>
#include <string.h>


#define MAX_STRING 100
void main()
{
  int date;
  char location[MAX_STRING];
  char apm;
  char weather[MAX_STRING];
  int ret;

  FILE *fp = fopen("weather.dat","w");

  while(1)
  {
    fputs("** 날씨 정보 입력 *****\n",stdout);

    fputs("날짜 : ",stdout);
    ret = scanf("%d",&date);
    fflush(stdin);
    if(ret == EOF)
      break;

    fprintf(fp,"%d",date);

    fputs("지역 : ",stdout);
    scanf("%s",location);
    fputs("\n",fp);
    fputs(location,fp);

    
    printf("오전/ 오후 : ");
    
    fputc(apm,fp);
    fflush(stdin);

    fputs("날씨 : ",stdout);
    gets(weather);
    fputs("\n",fp);
    fputs(weather,fp);

    fputs("\n",stdout);
  }

  fclose(fp);
  fputs("입력이 완료됐습니다\n",stdout);
  

    /* 
    printf("날짜를 입력하세요 : ");
    scanf("%d",&date);
    fprintf(fp,"%d",date);

    printf("지역을 입력하세요 : ");
    fgets(&location,MAX_STRING,stdin);
    fputs(&location,fp);

    printf("오전 or 오후를 입력하세요 : ");
    scanf("%c",&apm);
    fputc(apm,fp);

    printf("날씨를 입력하세요 : ");
    fgets(&weather,MAX_STRING,stdin);

    if(weather == EOF)
    {
      puts("프로그램을 종료합니다\n");
      exit(0);
    }
    else
    {
      fputs(&weather,fp);
    }
    */
  
}
