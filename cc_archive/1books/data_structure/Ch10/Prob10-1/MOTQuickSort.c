#include <stdio.h>

void Swap(int arr[], int idx1, int idx2)
{
	int temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}	

int MedianOfThree(int arr[], int left, int right)
{
	int samples[3] = {left, (left+right)/2, right};

	if(arr[samples[0]] > arr[samples[1]])
		Swap(samples, 0, 1);

	if(arr[samples[1]] > arr[samples[2]])
		Swap(samples, 1, 2);

	if(arr[samples[0]] > arr[samples[1]])
		Swap(samples, 0, 1);

	return samples[1];
}

int Partition(int arr[], int left, int right)
{
	int pIdx = MedianOfThree(arr, left, right);   // 피벗을 선택!
	int pivot = arr[pIdx];

	int low = left+1;
	int high = right;

	Swap(arr, left, pIdx);    // 피벗을 가장 왼쪽으로 이동

	printf("피벗: %d \n", pivot);

	while(low <= high)    // 교차되지 않을 때까지 반복
	{	
		while(pivot >= arr[low] && low <= right)
			low++;

		while(pivot <= arr[high] && high >= (left+1))
			high--;

		if(low <= high)    // 교차되지 않은 상태라면 Swap 실행
			Swap(arr, low, high);    // low와 high가 가리키는 대상 교환
	}

	Swap(arr, left, high);    // 피벗과 high가 가리키는 대상 교환
	return high;    // 옮겨진 피벗의 위치 정보 반환
}

void QuickSort(int arr[], int left, int right)
{
	if(left < right)
	{
		int pivot = Partition(arr, left, right);    // 둘로 나눠서 
		QuickSort(arr, left, pivot-1);    // 왼쪽 영역을 정렬
		QuickSort(arr, pivot+1, right);    // 오른쪽 영역을 정렬
	}
}

int main(void)
{
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

	int len = sizeof(arr) / sizeof(int);
	int i;

	QuickSort(arr, 0, sizeof(arr)/sizeof(int)-1);

	for(i=0; i<len; i++)
		printf("%d ", arr[i]);

	printf("\n");
	return 0;
}