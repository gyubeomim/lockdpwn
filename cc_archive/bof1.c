/*
  c ==> CTF, stack bof를 일으키는 예제 코드 마지막에 \x78\x56\x34\x12가 들어가면 FLAG를 반환한다
 */
#include <stdio.h>

int main(int argc, char *argv[])
{
  int zero = 0;
  char buffer[10];

  printf("buffer address\t= %x\n", (int)buffer);
  printf("zero address\t= %x\n", (int)&zero);

  fgets(buffer, 64, stdin);
  printf("zero = %d\n", zero);

  if (zero == 0x12345678)
  {
    printf("congrat! FLAG is l0ckd0wn\n");
  }
  return 0;
}
