#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  int a[3][3] = {1,2,3,
                 4,5,6,
                 7,8,9};
  int b[3][3] = {1,0,0,
                0,1,0,
                 0,0,1};

  int sum[3][3] ={0};

  for(int i =0; i < 3 ;i++ )
  {
    for(int j = 0; j < 3; j++)
    {
      for(int k =0; k <3; k++)
      {
        sum[i][k] += b[i][j]*a[j][k];
      }
    }
  }

  // Ãâ·Â
  for(int i =0 ; i<3 ;i++)
  {
    for(int j =0;j<3;j++)
    {
      printf("%d ",sum[i][j]);
    }
  }
  printf("\n");
  return 0;
}
