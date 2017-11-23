/*
  c tcpip ==> dup, dup2 함수를 사용해 파일디스크럽터를 복사해본 예제 코드
 */
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int cfd1, cfd2;
  char str1[] = "str1 \n";
  char str2[] = "str2 \n";

  cfd1 = dup(1);
  cfd2 = dup2(cfd1, 7);

  printf("fd1 = %d, fd2 = %d \n", cfd1, cfd2);
  write(cfd1, str1, sizeof(str1));
  write(cfd2, str2, sizeof(str2));

  close(cfd1);
  close(cfd2);

  write(1, str1, sizeof(str1));
  close(1);
  write(1, str2, sizeof(str2)); // 이 코드는 실행되지 않는다

  return 0;
}
