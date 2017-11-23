#include <stdio.h>
#include <string.h>

#define MAX_SPRING 100

int main()
{
	int day, day_f;
	char strRegion[MAX_SPRING], strRegion_f[MAX_SPRING];
	int ap=0, ap_f; // am or pm

	char strWeather_f[MAX_SPRING];

	FILE *fp = fopen("weather.dat","r");

	if (fp==NULL){
	puts("can't open weather.dat");
	return -1;
	}

	/* 검색 할날 짜정 보입  */

	fputs("검색 할날짜 및지 역정 보입  력  : ",stdout);
	fscanf(stdin, "%d %s %c", &day, strRegion, &ap );

	/* 비교 를위 한strRegion 의교  정 */
	sprintf(strRegion,"%s\n",strRegion);

	while(1){
	  fread(&day_f, sizeof(int),1,fp);
      if(feof(fp)!=0)
        break;

      fgets(strWeather_f, MAX_SPRING,fp);
      ap_f = fgetc(fp);
      fgets(strWeather_f,MAX_SPRING,fp);

      if(day==day_f &&
         !strcmp(strRegion, strRegion_f) && ap==ap_f)
      {
        fprintf(stdout, "date : %d \n", day_f);
        fprintf(stdout, "location : %s",strRegion_f);
        fprintf(stdout, "AM / PM : %c\n", ap_f);
        fprintf(stdout, "Weather : %s \n", strWeather_f);
        fclose(fp);
        puts("Searching complete");

        return 0;
    
      }
      
	}
    fclose(fp);
    puts("there's no data like that");
    return 0;
    
}
