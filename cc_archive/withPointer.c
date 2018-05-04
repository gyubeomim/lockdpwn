/*
 *  c ==> 해킹맛보기, 어셈블리용 포인터를 사용한 c 코드
 */
#include <stdio.h>

int inc(int *a)
{
  *a = *a + 1;
  return *a;
}

int main()
{
  int s, ret;

  s = 2;
  ret = inc(&s);
  printf("%d, %d\n", s, ret);

  return 0;
}
