/*
 * freescale c ==> i 값을 2진수로 변환시켜서 그 값에 따라 LED가 켜지고 꺼지는 코드2
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_sys.h"

vuint32_t i = 0;   // i를 선언한다

char SW = 0;     // 버튼을 누르는걸 인식하기 위해 SW, SWold를 선언한다
char SWold = 0;

int binary[4] = {0,0,0,0};  // LED를 깜빡이기 위해 2진수를 읽는 배열을 선언한다
int iBin = 0;               // i 값을 2진수로 변환시키는 iBin, Num을 선언한다
int Num = 0;       

void btnClickToIncrease();

int main(void) 
{
    initModesAndClock(); 		
	disableWatchdog();    		// 와치독 끄기
	enableIrq();		   		
	
	init_INTC();				
	init_Linflex0();

	/* CPR: Current Priority Register */
	INTC.CPR.B.PRI = 0;
	FMSTR_Init();  // 프리마스터 초기화

	// GPIO : global port input output
	// PCR  : pad control register
	SIU.PCR[48].R = 0x0100;  // Input 설정(SW) PD0

	SIU.PCR[52].R = 0x0200;  // Output LED 설정 PD4
	SIU.PCR[53].R = 0x0200;  // Output LED 설정 PD5
	SIU.PCR[54].R = 0x0200;  // Output LED 설정 PD6
	SIU.PCR[55].R = 0x0200;  // Output LED 설정 PD7

	while(1) 
	{
    	FMSTR_Poll(); // 프리마스터에 데이터 전송
	
		/*-------------------------------------------*/
		btnClickToIncrease();  // 버튼 클릭을 할 때마다 i값을 증가시킵니다
		iBin = i;   // i값을 읽어서 iBin 에 복사합니다 (2진수로 만들기 위해)

		// 루프를 돌면서
		while(1)
		{
			// Num값을 늘려가며 binary 배열에 iBin의 2진수 값을 입력합니다
			binary[Num] = iBin % 2 ;  
			iBin = iBin/2;    
			Num++;
		
			// binary 배열이 다 차면 루프를 나옵니다
			if(Num > 3)
			{
				Num = 0;
				break;
			}
		}

		// LED는 기본적으로 꺼져있습니다
		SIU.GPDO[52].R = 1;
		SIU.GPDO[53].R = 1;
		SIU.GPDO[54].R = 1;
		SIU.GPDO[55].R = 1;

		// 각 배열의 값을 읽으면서 값이 참이면 LED를 켭니다
		if(binary[0] == 1)
		{
			SIU.GPDO[52].R = 0;
		}
		if(binary[1] == 1)
		{
			SIU.GPDO[53].R = 0;
		}
		if(binary[2] == 1)
		{
			SIU.GPDO[54].R = 0;
		}
		if(binary[3] == 1)
		{
			SIU.GPDO[55].R = 0;
		}
	}
	return 0;
}

// 버튼 클릭을 인식하는 함수
void btnClickToIncrease()
{
	SW = SIU.GPDI[48].R;  // 버튼이 클릭되면 SW 값을 0으로 변경합니다

	// SWold 값을 이용해 버튼을 한 번씩 누를때 1씩 증가하도록 만든다
	if (SWold > SW)
	{
		i++;
	}
	SWold = SW;
}

