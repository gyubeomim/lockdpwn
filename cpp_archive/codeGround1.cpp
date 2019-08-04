/*
  c++ ==> 코드그라운드, 할인권이라는 basic난이도 문제를 풀어본 코드

  https://www.codeground.org/practice/practiceProbView.do?probId=46
  생각보다 졸라 어렵네..
*/
#include <cstdio>
#include <iostream>

#define MAXNUM 10000

using namespace std;

int main(int argc, char** argv)
{
  setbuf(stdout, NULL);

  int T;
  int test_case;

  int N;
  int M;
  int kValue;
  int pValue;
  int via;
  int saleticket = 0;


  scanf("%d", &T);

  for(test_case = 1; test_case <= T; test_case++)
  {
    while(1)
    {
      // N, M ,K
      scanf("%d %d %d", &N, &M, &kValue);
      if (N > 100 || N < 1)
      {
        continue;
      }
      if(M < 1 || M > N*(N-1)/2)
      {
        continue;
      }
      if(kValue < 1 || kValue > MAXNUM)
      {
        continue;
      }
      //printf("infinite loop\n");
      break;
    }
    int ABi[M][2];
    int Ci[M];



    for(int i = 0; i < M; i++)
    {
      scanf("%d %d %d", &ABi[i][0], &ABi[i][1], &Ci[i]);

      if(ABi[i][0] > N || ABi[i][1] > N || Ci[i] > MAXNUM || Ci[i] < 1)
      {
        i = 0;
        continue;
      }
      //     printf("c is : %d\n", Ci[i]);
      //      printf("ival : %d\n",i);
    }

    // P 값 받는다
    scanf("%d", &pValue);
    //printf("[+] here is p");
    int find[pValue][2];

    for(int j = 0 ; j < pValue ; j++)
    {
      scanf("%d %d", &find[j][0], &find[j][1]);
    }

    printf("\nCase #%d\n", test_case);

    for(int k = 0; k < pValue ; k++)
    {
      //      printf("[%d]th case : %d,%d\n",k,find[k][0],ABi[k][0]);

      for(int x = 0; x < pValue ; x++)
      {
        if(find[k][0] == ABi[x][0] )
        {
          via = ABi[x][1];
          for(int a = 0 ; a < pValue ; a++)
          {
            if(via == ABi[a][0])
            {
              if(find[k][1] == ABi[a][1])
              {
                if(a != x)
                {
                  Ci[a] += Ci[x];
                }
                if(Ci[a] > kValue)
                {
                  saleticket++;
                }
              }
            }
            if(via == ABi[a][1])
            {
              if(find[k][1] == ABi[a][0])
              {
                if(a != x)
                {
                  Ci[a] += Ci[x];
                }
                if(Ci[a] > kValue)
                {
                  saleticket++;
                }
              }
            }
          }
        }
        if(find[k][0] == ABi[x][1])
        {
          via = ABi[x][0];
          for(int a = 0 ; a < pValue ; a++)
          {
            if(via == ABi[a][0])
            {
              if(find[k][1] == ABi[a][1])
              {
                if(a != x)
                {
                  Ci[a] += Ci[x];
                }
                if(Ci[a] > kValue)
                {
                  saleticket++;
                }
              }
            }
            if(via == ABi[a][1])
            {
              if(a != x)
              {
                Ci[a] += Ci[x];
              }
              if(find[k][1] == ABi[a][0])
              {
                if(a != x)
                {
                  Ci[a] += Ci[x];
                }
                if(Ci[a] > kValue)
                {
                  saleticket++;
                }
              }
            }
          }
        }
      }
    }
    printf("%d\n",saleticket);

  }

  return 0;
}
