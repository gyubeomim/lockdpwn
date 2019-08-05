/*
  c ==> CTF, GOT overwrite 공격을 시험해본 예제 코드
 */
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char str[128];
  fgets(str, 128, stdin);
  printf(str);

  fgets(str, 128, stdin);
  printf("%d\n", strlen(str));

  return 0;
}
