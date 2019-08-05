/*
 * freescale ==> 1초마다 7세그먼트를 1씩 증가시키면서 Dot Point는 0.1초마다 깜빡거리는 코드
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_sys.h"

// 0 ~ F 까지 배열로 저장해논다
char hex[16] = {0x03 , 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1B, 0x01, 0x09,0x11,0x01,0x63,0x03,0x61,0x71};

// 공용체를 선언한다
struct LED_tag
{
	union
	{
		vuint8_t R;
		struct
		{
			vuint8_t A:1;
			vuint8_t B:1;
			vuint8_t C:1;
			vuint8_t D:1;
			vuint8_t E:1;
			vuint8_t F:1;
			vuint8_t G:1;
			vuint8_t DP:1;
		}B;
	}LEDSET;
};

struct LED_tag LED;
vuint8_t input_val =0;
vuint8_t dotpoinblinker = 0;

// 0.1초마다 카운트를 수행하는 함수
void CNT()
{
	dotpoinblinker++;

	// dotpoinblinker가 10이되면 input_val이 하나씩 증가한다
	if(dotpoinblinker == 10)
	{
		input_val++;
		dotpoinblinker = 0;
	}
	
	if(input_val == 16)
	{
		input_val = 0 ;
	}
	
	PIT.CH[0].TFLG.B.TIF = 1;
}

void output_pin()
{
	SIU.PCR[48].R  = 0x0200;
	SIU.PCR[49].R  = 0x0200;
	SIU.PCR[50].R  = 0x0200;
	SIU.PCR[51].R  = 0x0200;
	SIU.PCR[52].R  = 0x0200;
	SIU.PCR[53].R  = 0x0200;
	SIU.PCR[54].R  = 0x0200;
	SIU.PCR[55].R  = 0x0200;
}

void display_seg()
{
	LED.LEDSET.R = hex[(input_val % 16)];

	if(dotpoinblinker % 2 == 0)
	{
		SIU.GPDO[55].B.PDO = 1;
	}
	else
	{
		SIU.GPDO[55].B.PDO = 0;
	}
	SIU.GPDO[48].B.PDO = LED.LEDSET.B.A;
	SIU.GPDO[49].B.PDO = LED.LEDSET.B.B;
	SIU.GPDO[50].B.PDO = LED.LEDSET.B.C;
	SIU.GPDO[51].B.PDO = LED.LEDSET.B.D;
	SIU.GPDO[52].B.PDO = LED.LEDSET.B.E;
	SIU.GPDO[53].B.PDO = LED.LEDSET.B.F;
	SIU.GPDO[54].B.PDO = LED.LEDSET.B.G;
}

// PIT 초기화 코드
void init_PIT()
{
	PIT.PITMCR.R = 0x00000001;  // Enable PIT and Config Stop in debug mode.

	// PIT channel 0 초기화 (0.25초마다 생성)
	PIT.CH[0].LDVAL.R = 6400000; // 64000000 // Timeout = (64M * 1 sec / 64M sysclocks = 1s)
	PIT.CH[0].TCTRL.R = 0x3;  // Enable PIT0 interrupt & start PIT counting
	
	PIT.PITMCR.R = 0x00000000;	 // Freeze를 초기화가 끝나고 풀어줘야 한다
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
	
	INTC_InstallINTCInterruptHandler(CNT,59,1); // PIT0ISR 함수를 59번(PIT channel 0)에 6번 우선순위로 초기화시킨다
	
	// D0 ~ D7 포트를 출력으로 설정한다
	output_pin();

	while(1) 
	{
		FMSTR_Recorder();
		FMSTR_Poll();

		// 세그먼트를 반짝거린다
		display_seg();
	}
}

