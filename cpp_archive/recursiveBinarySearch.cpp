#include <stdio.h>

int BsearchRecur(int ar[], int first, int last, int target)
{
	int mid;
	if (first > last) 
	{
		return -1;
	}
	mid = (first + last) /2;

	if (ar[mid] == target) 
	{
		return mid;
	}
	else if (ar[mid] > target)
	{
		 return BsearchRecur(ar, first, mid - 1, target);
	}
	else if (ar[mid] < target)
	{
		 return BsearchRecur(ar, mid + 1, last, target);
	}
}

int main(int argc, const char *argv[])
{
	int arr[] = {1,3,5,7,9};
	int idx;

	idx = BsearchRecur(arr, 0, sizeof(arr)/sizeof(int)-1, 7);
	if (idx == -1) 
	{
		printf("fail\n");
	}
	else 
	{
		printf("target index : %d\n", idx);
	}

	idx = BsearchRecur(arr, 0, sizeof(arr)/sizeof(int)-1, 4);
	if (idx == -1) 
	{
		printf("fail\n");
	}
	else 
	{
		printf("target index : %d\n", idx);
	}


	return 0;
}



