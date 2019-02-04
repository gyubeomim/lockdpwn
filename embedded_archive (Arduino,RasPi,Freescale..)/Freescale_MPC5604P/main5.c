/*
 * freescale c ==> i 값을 2진수로 변환시켜서 그 값에 따라 LED가 켜지고 꺼지는 코드
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_sys.h"

vuint32_t i = 0;			    /* Dummy idle counter */

char SW1 =0;
char SWold = 0;

void LED_Ctr();
void btnClickToIncrease();

int main(void) 
{
    initModesAndClock(); 		
	disableWatchdog();    		// 와치독 끄기
	enableIrq();		   		
	
	init_INTC();				
	init_Linflex0();

	INTC.CPR.B.PRI = 0;
	/* CPR: Current Priority Register */

	FMSTR_Init();  // 프리마스터 초기화

	// GPIO : global port input output
	// PCR  : pad control register
	SIU.PCR[48].R = 0x0100;  // Input 설정(SW1) PD0
	SIU.PCR[49].R = 0x0100;  // Input 설정(SW1) PD1
	SIU.PCR[50].R = 0x0100;  // Input 설정(SW1) PD2
	SIU.PCR[51].R = 0x0100;  // Input 설정(SW1) PD3

	SIU.PCR[52].R = 0x0200;  // Output 설정(LED1) PD4
	SIU.PCR[53].R = 0x0200;  // Output 설정(LED1) PD5
	SIU.PCR[54].R = 0x0200;  // Output 설정(LED1) PD6
	SIU.PCR[55].R = 0x0200;  // Output 설정(LED1) PD7

	while(1) 
	{
    	FMSTR_Poll(); // 프리마스터에 데이터 전송
	
		/*-------------------------------------------*/

		btnClickToIncrease();

		SIU.GPDO[52].R = 1;
		SIU.GPDO[53].R = 1;
		SIU.GPDO[54].R = 1;
		SIU.GPDO[55].R = 1;

		if(i & 0x01)
		{
			SIU.GPDO[52].R = 0;
		}
		if(i & 0x02)
		{
			SIU.GPDO[53].R = 0;
		}
		if(i & 0x04)
		{
			SIU.GPDO[54].R = 0;
		}
		if(i & 0x08)
		{
			SIU.GPDO[55].R = 0;
		}
	}
	return 0;
}

void btnClickToIncrease()
{
	SW1 = SIU.GPDI[48].R;

	// SWold 값을 이용해 버튼을 한 번씩 누를때 1씩 증가하도록 만든다
	if (SWold > SW1)
	{
		i++;
	}
	// i 값이 10이면 0으로 초기화한다
	if (i > 10)
	{
		i = 0;
	}

	SWold = SW1;
}

