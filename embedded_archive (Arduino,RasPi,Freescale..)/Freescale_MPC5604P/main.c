/*
 *  freescale C ==> 스위치를 누르면 LED가 꺼졌다 켜졌다 하는 코드
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_sys.h"


vuint32_t i = 0;			    /* Dummy idle counter */

char SW1 =0;
char SW2 =0;
char SW3 =0;
char SW4 =0;

void main(void) 
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
	SIU.PCR[48].R = 0x0100;  // Input 설정(SW1)
	SIU.PCR[49].R = 0x0100;  // Input 설정(SW2)
	SIU.PCR[50].R = 0x0100;  // Input 설정(SW3)
	SIU.PCR[51].R = 0x0100;  // Input 설정(SW4)


	SIU.PCR[52].R = 0x0200;  // Output 설정(LED1)
	SIU.PCR[53].R = 0x0200;  // Output 설정(LED2)
	SIU.PCR[54].R = 0x0200;  // Output 설정(LED3)
	SIU.PCR[55].R = 0x0200;  // Output 설정(LED4)


	while(1) 
	{
    	FMSTR_Poll(); // 프리마스터에 데이터 전송
	
		/*-------------------------------------------*/

		SW1 = SIU.GPDI[48].R;
		SW2 = SIU.GPDI[49].R;
		SW3 = SIU.GPDI[50].R;
		SW4 = SIU.GPDI[51].R;
	

		if(SW1)
		{
			SIU.GPDO[52].R = 1;
		}
		else
		{
			SIU.GPDO[52].R = 0;
		}

		if(SW2)
		{
			SIU.GPDO[53].R = 1;
		}
		else
		{
			SIU.GPDO[53].R = 0;
		}

		if(SW3)
		{
			SIU.GPDO[54].R = 1;
		}
		else
		{
			SIU.GPDO[54].R = 0;
		}
		
		if(SW4)
		{
			SIU.GPDO[55].R = 1;
		}
		else
		{
			SIU.GPDO[55].R = 0;
		}


	}
}




