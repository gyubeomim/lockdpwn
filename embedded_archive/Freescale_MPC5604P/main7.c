/*
 * freescale C ==> Interrupt를 사용해서 LED를 1초마다 깜빡거리게 하는 코드
 * 					왜그런지 모르겠지만 21초까지만 지속되고 이후에는 작동을 멈춘다
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_sys.h"

// PIT 초기화 코드
void init_PIT()
{
	PIT.PITMCR.R = 0x00000001;  // Enable PIT and Config Stop in debug mode.

	// PIT channel 0 초기화 (1초마다 생성)
	PIT.CH[0].LDVAL.R = 0x03D09000; // 64000000 // Timeout = (64M * 1 sec / 64M sysclocks = 1s)
	PIT.CH[0].TCTRL.R = 0x3;  // Enable PIT0 interrupt & start PIT counting

	// PIT channel 1 초기화 (2초마다 생성)
	PIT.CH[1].LDVAL.R = 0x07A12000; // 128000000 // Timeout = (128M * 1 sec / 64M sysclocks = 2s)
	PIT.CH[1].TCTRL.R = 0x3;  // Enable PIT0 interrupt & start PIT counting
}

// 인터럽트 함수 (1초마다)
void PIT0ISR()
{
	SIU.GPDO[52].R = 0;		
	SIU.GPDO[53].R = 1;		
	SIU.GPDO[54].R = 0;		
	SIU.GPDO[55].R = 1;

	PIT.CH[0].TFLG.B.TIF = 1;  // Clear PIT0 flag
}

// 인터럽트 함수 (2초마다)
void PIT1ISR()
{
	SIU.GPDO[52].R = 1;		
	SIU.GPDO[53].R = 0;		
	SIU.GPDO[54].R = 1;		
	SIU.GPDO[55].R = 0;

	PIT.CH[1].TFLG.B.TIF = 1;  // Clear PIT1 flag
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
	INTC_InstallINTCInterruptHandler(PIT1ISR,60,6); // PIT1ISR 함수를 60번(PIT channel 1)에 6번 우선순위로 초기화시킨다 

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
	}
}




