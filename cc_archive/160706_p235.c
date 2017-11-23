#include <stdio.h>
#include <string.h>


#define MAX_STRING 100


void main()
{
  int day, day_f;
  char strRegion[MAX_STRING], strRegion_f[MAX_STRING];
  int ap = 0, ap_f;

  char strWeather_f[MAX_STRING];

  FILE *fp = fopen("weather.dat","r");

  fputs("검색할 날짜 및 지역 정보 입력 : ",stdout);
  fscanf(stdin,"%d %s %c",&day, strRegion,&ap);

  sprintf(strRegion,"%s\n",strRegion);

  while(1)
  {
    fread(&day_f, sizeof(int),1,fp);
    
    if(feof(fp)!=0)
      break;

    fgets(strRegion_f, MAX_STRING,fp);
    ap_f = fgetc(fp);
    fgets(strWeather_f, MAX_STRING,fp);


    if(day == day_f && !strcmp(strRegion,strRegion_f) && ap == ap_f)
    {
      fprintf(stdout, "날짜: %d\n", day_f);
      fprintf(stdout, "지역: %s\n", strRegion_f);
      fprintf(stdout, "오전/오후: %c\n", ap_f);
      fprintf(stdout, "날씨: %s\n", strWeather_f);
      fclose(fp);
      puts("검색이 완료되었습니다\n");
      exit(0);
    }

    fclose(fp);
    puts("해당 날짜 및 데이터가 존재하지 않습니다");
    exit(0);
  }
    
  
}
