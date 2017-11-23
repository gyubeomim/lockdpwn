#include <stdio.h>
#include <string.h>
#define MAX_STRING 100



int main(){

  char str[MAX_STRING] = {'A','B','\n',0};

  /* 파일개방 */
  FILE* fp_txt = fopen("text.txt","w");
  FILE* fp_bin = fopen("binary.bin","wb");


  /* \r \n */
  printf("10진수 \\r \\n 은각각 %d, %d입니다\n",'\r','\n');
  printf("16진수 \\r \\n 은각각 %X, %X입니다\n",'\r','\n');


  /* 문자열삽입 */

  fputs(str,fp_txt);
  fputs(str,fp_bin);

  fputs(str,fp_txt);
  fputs(str,fp_bin);

  puts("문자열입력이완료되었습니다");

  /* 파일종 료*/

  fclose(fp_txt);
  fclose(fp_bin);

  return 0;
    
  
}




















