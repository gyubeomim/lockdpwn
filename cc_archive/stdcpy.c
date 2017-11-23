/*
  c tcpip ==> 표준입출력함수 fget, fputs, fopen을 사용해 데이터 전송속도를 확인하는 예제 코드
                빠르다고 한다
 */
#include <stdio.h>
#include <fcntl.h>

#define BUF_SIZE 3

int main(int argc, char *argv[])
{
  FILE *fp1, *fp2;
  char buf[BUF_SIZE];

  fp1 = fopen("news.txt", "r");
  fp2 = fopen("cpy.txt", "w");

  while (fgets(buf, BUF_SIZE, fp1) != NULL)
  {
    fputs(buf, fp2);
  }

  fclose(fp1);
  fclose(fp2);
  return 0;
}
