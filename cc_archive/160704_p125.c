#include <stdio.h>

void SortArr(int *arr, int num);
void ReadAndSortPrint(int number);

void main()
{

  int num;
  fputs("입력할 정수의 개수 : ",stdout);
  scanf("%d", &num);

  ReadAndSortPrint(num);
  return 0;
  
}

void SortArr(int *arr,int num)
{
  int i,j,tmp;

  for(i=0; i<num-1; i++)
  {
    for(j=0;j<(num-i)-1;j++)
    {
      if(arr[j]>arr[j+1])
      {
        tmp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = tmp;
      }
    }
  }

  
}

void ReadAndSortPrint(int number)
{
  //int arr[number];

  int *arr;
  int i;

  
  arr = (int*)malloc(number*sizeof(int));

  for(i=0; i<number; i++)
  {
    printf("%d 번째 입력: ",i+1);
    scanf("%d", &arr[i]);
  }

  SortArr(arr,number);

  
  puts("입력 숫자의 정렬된 출력");

  for(i=0; i<number; i++)
    printf("%d ",arr[i]);
  printf("\n");


  free(arr);
}


