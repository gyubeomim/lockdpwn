#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 

int main(int argc, char *argv[])
{
	int i, j, h, dan, col, row, begin;

	printf(" 시작단: ");  scanf("%d", &begin);
	printf(" 몇단씩: "); scanf("%d", &col);
	printf(" 끝  단: "); scanf("%d", &dan);

	if ( col > 5 )
		system("mode con cols=130");

	row = (dan - begin)/col + 1;
	for(i = 1 ;i <= row ; i++)
	{
		//   int jun = i* col + begin;  //for문에 시작부분과 조건부에 넣어서 코드를
		for(j=1;j<10;j++)       		//좀더 정렬되어 보이게 할 수 있습니다.
		{
			if(j==1)
			{
				putchar('\n');
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
				for( h= i * col + begin - col ; ( h < i * col + begin ) && ( h <= dan) ; h++)
					printf("   < %2d 단 >   ", h);
				putchar('\n');
				for( h= i * col + begin - col ; ( h < i * col + begin ) && ( h <= dan) ; h++)
					printf(" ============= ");
				putchar('\n');
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
			}
			for( h= i * col + begin - col ; ( h < i * col + begin ) && ( h <= dan) ; h++)
				printf(" %2d * %2d = %3d ", h, j, h*j);
			putchar('\n');
		}
	}

	if (col > 5)
	{
		printf("\n 화면을 지우고 화면크기를 기본값으로 되돌립니다. . . \n" \
				" 가로 출력단수가 5이하이면 화면을 지우지 않습니다.\n");
		system(" pause");
		system("mode con cols=80");
	}

	return 0;
}
