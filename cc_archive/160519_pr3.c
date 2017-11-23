#include <stdio.h>

#define MAX_STRING 100

int main(){

  int day;
  int ap; // am or pm
  int ret;
  char str[MAX_STRING];


  FILE * fp = fopen("weather.dat","w");
  if (fp=NULL)
  {
    puts("파일 'weather.dat' 가 열리지 않았습니다");
    return -1;
  }


  while(1)
  {
    fputs("** 날씨 정보 입력 **** \n",stdout);


    /* 1, 날짜 입력 : 숫자 */
    fputs("날짜 : ",stdout);
    ret = fscanf(stdin, "%d",&day);
    fflush(stdin);
    if(ret==EOF);

    if(ret==EOF)
      break;
    fwrite(&day, sizeof(int),1,fp);



    /* 2. 지역 입력 : 문자열 */
    fputs("지역 : ",stdout);
    fgets(str,MAX_STRING, stdin);
    fputs(str,fp);



    /* 3. 오전/오후 : 문자*/
    fputs("오전(A)/오후(P) : ",stdout);
    ap = fgetc(stdin);
    fputc(ap,fp);
    fflush(stdin);



    /* 4. 날씨입력 : 문자열 */
    fputs("날씨 : ",stdout);
    fgets(str,MAX_STRING,stdin);
    fputs(str,fp);

    fputs("\n",stdout); // 한줄 건너뛰기
  }
		
  fclose(fp);
  puts("입력이 완료되었습니다");
  return 0;

}
























