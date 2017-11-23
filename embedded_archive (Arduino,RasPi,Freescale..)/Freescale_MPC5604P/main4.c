/*
 * freescale C ==> 가변저항 값에 따라 LED가 켜지고 꺼지는 코드
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_sys.h"

// Analog 값 ==> Digital 값으로 변환하기 위한 R_adc 선언
int R_adc = 0;

// volatge 값
int volt = 0;

// ADC 초기화 코드
void init_ADC1()
{
	ADC_1.MCR.B.ABORT = 1;
	ADC_1.MCR.B.OWREN = 0;
	ADC_1.MCR.B.WLSIDE = 0;
	ADC_1.MCR.B.MODE = 0;
	ADC_1.MCR.B.CTUEN = 0;
	ADC_1.MCR.B.ADCLKSEL = 0;
	ADC_1.MCR.B.ACK0 = 0;
	ADC_1.MCR.B.PWDN = 0;

	ADC_1.CTR[0].R = 0x00008208;   // 0000 0000 0000 0000 1000 0010 0000 1000
	// Phase Duration Latch(INPLATCH) : Enabled(Always) 	1 clock Cycle
	// Input Sampling Duration(INPSAMP) : 8 (INPSAMP >= 8) 	7 clock Cycles
	// Input Comparison Duration(INPCMP) : 0b01 			12 clock Cycles
	// Conversion Time : 7 + 12 + 1 (Tck) 					20 clock Cycles 

	ADC_1.NCMR[0].R = 0x00000020; // Select ANS5 Inputs for conversion
	ADC_1.CDR[5].R = 0x00000000; // Channel[5] Set Default
	ADC_1.MCR.B.ABORT = 0; // 
}

// ADC 변환함수
// 순식간에 NSTART가 1 ==> 0 으로 바뀌고 R_adc에 값을 넣는다고 한다
// ADC 값을 받는 동안 무의미한 클락을 사용하라고 asm("nop")을 사용한다
void ADCRead_1()
{
	ADC_1.MCR.B.NSTART = 1;  // Module 1 Conversion Start
	asm("nop");  // 사실 nop은 안써도 상관없긴 하다고 한다
	
	while(ADC_1.MCR.B.NSTART)
	{
		asm("nop");  // 사실 nop은 안써도 상관없긴 하다고 한다
	}

	// 가변저항에 따라 바뀌는 값을 R_adc에 넣는다
	R_adc = ADC_1.CDR[5].B.CDATA;
}

void main(void) 
{
	initModesAndClock();
	disableWatchdog();    		
	enableIrq();		   		
	
	init_INTC();				
	init_Linflex0();
	init_ADC1();
	
	INTC.CPR.B.PRI = 0;
	FMSTR_Init();

	SIU.PCR[64].R = 0x2400;  // E0 포트 설정 (ADC_1 가변저항 파란색 움직이는거 사용한다고 선언)
							 // 0100 0010 0000 0000
	SIU.PCR[24].R = 0x2000;  // B8 포트 설정 (ADC_0 사용)

	SIU.PCR[52].R = 0x0200;  // D4 포트 LED 설정(LED1)
	SIU.PCR[53].R = 0x0200;  // D5 포트 LED 설정(LED2)
	SIU.PCR[54].R = 0x0200;  // D6 포트 LED 설정(LED3)
	SIU.PCR[55].R = 0x0200;  // D7 포트 LED 설정(LED4)

	while(1) 
	{
		FMSTR_Recorder();
		FMSTR_Poll();

		// ADC 변환함수 실행
		ADCRead_1();

		// voltage 값을 읽는다
		volt = R_adc * 5.0 /1024.0;
		if (R_adc == 1023)
		{
			volt = 5;
		}

		// 가변저항 값이 1024등분되고 이 값에 따라 LED를 ON/OFF 시킨다
		if ( R_adc<= 100)
		{
			SIU.GPDO[52].R = 1;		
			SIU.GPDO[53].R = 1;		
			SIU.GPDO[54].R = 1;		
			SIU.GPDO[55].R = 1;	
		}
		else if(R_adc >= 100 && R_adc <= 250)
		{
			SIU.GPDO[52].R = 0;		
			SIU.GPDO[53].R = 1;		
			SIU.GPDO[54].R = 1;		
			SIU.GPDO[55].R = 1;		
		}
		else if(R_adc >= 250 && R_adc <= 500)
		{
			SIU.GPDO[52].R = 0;		
			SIU.GPDO[53].R = 0;		
			SIU.GPDO[54].R = 1;		
			SIU.GPDO[55].R = 1;	
		}
		else if (R_adc >= 500 && R_adc <= 750)
		{
			SIU.GPDO[52].R = 0;		
			SIU.GPDO[53].R = 0;		
			SIU.GPDO[54].R = 0;		
			SIU.GPDO[55].R = 1;	
		}
		else
		{
			SIU.GPDO[52].R = 0;		
			SIU.GPDO[53].R = 0;		
			SIU.GPDO[54].R = 0;		
			SIU.GPDO[55].R = 0;	
		}
	}
}




