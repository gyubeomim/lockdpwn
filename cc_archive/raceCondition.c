/*
 *	c ==> 해킹맛보기, 4개의 스레드로 레이스컨디션을 만들어 본 코드
 */
#include <stdio.h>
#include <Windows.h>

const int kLoopCount = 4 * 100;
const int kNumThread = 4;
const int kIncreaseLoopCount = 100;
int total_count = 0;

DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
	int temp = total_count;

	for (int i = 0; i < kIncreaseLoopCount; i++)
	{
		temp++;
	}
	total_count = temp;

	return 0;
}

void concurrent_solver()
{
	total_count = 0;
	HANDLE hThreadArray[kNumThread];
	DWORD dwThreadArray[kNumThread];

	for (int i = 0; i < kNumThread; i++)
	{
		hThreadArray[i] = CreateThread(
			NULL,
			0,
			MyThreadFunction,
			NULL,
			0,
			&dwThreadArray[i]);
	}

	WaitForMultipleObjects(kNumThread, hThreadArray, TRUE, INFINITE);

	for (int i = 0; i < kNumThread; i++)
	{
		CloseHandle(hThreadArray[i]);
	}
}

int main()
{
	while (1)
	{
		concurrent_solver();

		printf("total count = %d\n", total_count);
		if (total_count != kLoopCount)
		{
			getchar();
		}
	}
	return 0;
}


