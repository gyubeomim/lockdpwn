#include <stdio.h>

long combi(int,int);

int main()
{
  int n,r;

  for (n=0;n<=5;n++)
  {
    for (r=0;r<=n;r++)
    {
      printf("%d C %d = %ld    ",n,r,combi(n,r));
    }
    printf("\n");
  }
  return 0;
}

long combi(int n, int r)
{
  int i;
  long p =1;

  for (i=1;i<=r;i++)
  {
    p = p*(n-i+1)/i;
  }
  return p;

}































