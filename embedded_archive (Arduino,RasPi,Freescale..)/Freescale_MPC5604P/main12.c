/*
 *	freescale c ==> Pit0cnt 값이 0.25초마다 계속 인터럽트로 증가해서 
 *					그 값을 2진수화시켜서 LED가 ON/OFF되는 코드
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_sys.h"

// PIT 초기화 코드
void init_PIT()
{
	PIT.PITMCR.R = 0x00000001;  // Enable PIT and Config Stop in debug mode.

	// PIT channel 0 초기화 (0.25초마다 생성)
	PIT.CH[0].LDVAL.R = 0x00F42400; // 64000000 // Timeout = (64M * 1 sec / 64M sysclocks = 1s)
	PIT.CH[0].TCTRL.R = 0x3;  // Enable PIT0 interrupt & start PIT counting

	PIT.PITMCR.R = 0x00000000;	 // Freeze를 초기화가 끝나고 풀어줘야 한다
}

vuint32_t Pit0cnt = 0;
int goMinus = 0;
int LED1=0,LED2=0,LED3=0,LED4=0;

void PIT0ISR()
{
	if(goMinus)
	{
		Pit0cnt--;
	}
	else 
	{
		Pit0cnt++;
	}

	if (Pit0cnt == 15)
	{
		goMinus = 1;
	}
	
	if(Pit0cnt == 0)
	{
		goMinus = 0;
	}
	
	PIT.CH[0].TFLG.B.TIF = 1;  // Clear PIT0 flag
}

void main(void) 
{
	initModesAndClock();
	disableWatchdog();    		
	enableIrq();		   		
	
	init_INTC();				
	init_Linflex0();
	init_PIT();  // PIT를 초기화시킨다
	
	INTC.CPR.B.PRI = 0;
	FMSTR_Init();
	
	INTC_InstallINTCInterruptHandler(PIT0ISR,59,6); // PIT0ISR 함수를 59번(PIT channel 0)에 6번 우선순위로 초기화시킨다

	SIU.PCR[48].R = 0x0100;  // D0 포트 스위치 설정
	SIU.PCR[49].R = 0x0100;  // D1 포트 스위치 설정
	SIU.PCR[50].R = 0x0100;  // D2 포트 스위치 설정
	SIU.PCR[51].R = 0x0100;  // D3 포트 스위치 설정

	SIU.PCR[52].R = 0x0200;  // D4 포트 LED 설정(LED1)
	SIU.PCR[53].R = 0x0200;  // D5 포트 LED 설정(LED2)
	SIU.PCR[54].R = 0x0200;  // D6 포트 LED 설정(LED3)
	SIU.PCR[55].R = 0x0200;  // D7 포트 LED 설정(LED4)

	while(1) 
	{
		FMSTR_Recorder();
		FMSTR_Poll();

		SIU.GPDO[52].R = 1;
		SIU.GPDO[53].R = 1;
		SIU.GPDO[54].R = 1;
		SIU.GPDO[55].R = 1;

		if(Pit0cnt & 0x01)
		{
			SIU.GPDO[52].R = 0;
		}
		if(Pit0cnt & 0x02)
		{
			SIU.GPDO[53].R = 0;
		}
		if(Pit0cnt & 0x04)
		{
			SIU.GPDO[54].R = 0;
		}
		if(Pit0cnt & 0x08)
		{
			SIU.GPDO[55].R = 0;
		}

		LED1 = SIU.GPDO[52].R;
		LED2 = SIU.GPDO[53].R * 2;
		LED3 = SIU.GPDO[54].R * 3;
		LED4 = SIU.GPDO[55].R * 4;
	}
}




