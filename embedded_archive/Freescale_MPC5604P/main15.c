/*
 *	freescale c ==> flexPWM + Interrupt를 활용해서 0.5초마다 PWM1_X 값이 +320 , -320이 되는 코드 
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_base.h"
#include "init_sys.h"

int flag = 0;
int PWM1_X =0;
void increasePWM();              
void init_PWM();
void PWM_OUT();
void init_PIT();

int main(void)
{
	initModesAndClock();
	disableWatchdog();
	enableIrq();

	INTC.CPR.B.PRI = 0;
	FMSTR_Init();
	init_INTC();
	init_Linflex0();
	init_PIT();   // 인터럽트를 초기화시킨다
	init_PWM();   // PWM을 초기화시킨다

	SIU.PCR[52].R = 0x0C00; //PWM B[3]  핀설정

	// PWM1_X 값을 증가시키기 위해 인터럽트를 사용한다
	INTC_InstallINTCInterruptHandler(increasePWM,59,1); 

	//- Loop forever *-
	while(1)
	{
		FMSTR_Recorder();
		FMSTR_Poll();

		PWM_OUT();
	}
}

void increasePWM()
{
	if (flag == 1)
	{
		PWM1_X -= 320;

		if(PWM1_X <= 0)
		{
			flag = 0;
		}
	}
	else
	{
		PWM1_X += 320;		

		if(PWM1_X >= 3199)
		{
			flag = 1;
		}
	}
	PIT.CH[0].TFLG.B.TIF = 1; // 와 이코드때문에 구현이 안된거였어 ㅡㅡ
}

// PIT 초기화 코드
void init_PIT()
{
	PIT.PITMCR.R = 0x00000001;  // Enable PIT and Config Stop in debug mode.

	// PIT channel 0 초기화 (초마다 생성)
	PIT.CH[0].LDVAL.R = 32000000; // 64000000 // Timeout = (64M * 1 sec / 64M sysclocks = 1s)
	PIT.CH[0].TCTRL.R = 0x3;  // Enable PIT0 interrupt & start PIT counting

	PIT.PITMCR.R = 0x00000000;	 // Freeze를 초기화가 끝나고 풀어줘야 한다
}

// PWM 초기화 코드
void init_PWM(void)
{
	// ex) 0b0111 : 모듈 0 ~ 2번을 사용한다
	FLEXPWM_0.OUTEN.B.PWMA_EN = 0b1000; // PWM 모듈 3번  사용 하는 겁니다.
	FLEXPWM_0.OUTEN.B.PWMB_EN = 0b1000;
	FLEXPWM_0.OUTEN.B.PWMX_EN = 0b0000; // PWMX는 사용하지 않는다

	FLEXPWM_0.MASK.R = 0x0000;

	FLEXPWM_0.SWCOUT.R = 0x00ff;

	FLEXPWM_0.SUB[3].INIT.R = 0xffff - 0x0C80 + 1;   // 보수 -3200 : 초기값을 (-)로 설정해 중간값이 0이 되게 한다  
	FLEXPWM_0.SUB[3].VAL[0].R = 0;       // 0부터
	FLEXPWM_0.SUB[3].VAL[1].R = 0x0C80;  // 0x0C80 : 3200까지 

	FLEXPWM_0.SUB[3].CTRL2.B.DBGEN = 0;
	FLEXPWM_0.SUB[3].CTRL2.B.WAITEN = 0;
	FLEXPWM_0.SUB[3].CTRL2.B.INDEP = 0;  // 이부분을 1로 셋팅 하시면 VAL[4], VAL[5] 에도 듀티가 변하도록 입력하셔야 합니다.
	FLEXPWM_0.SUB[3].CTRL2.B.PWMA_INIT = 0;
	FLEXPWM_0.SUB[3].CTRL2.B.PWMB_INIT = 0;
	FLEXPWM_0.SUB[3].CTRL2.B.PWMX_INIT = 0;
	FLEXPWM_0.SUB[3].CTRL2.B.INIT_SEL = 0b00;
	FLEXPWM_0.SUB[3].CTRL2.B.FRCEN = 0;
	FLEXPWM_0.SUB[3].CTRL2.B.FORCE = 0;
	FLEXPWM_0.SUB[3].CTRL2.B.FORCE_SEL = 0b000;
	FLEXPWM_0.SUB[3].CTRL2.B.RELOAD_SEL = 0;
	FLEXPWM_0.SUB[3].CTRL2.B.CLK_SEL = 0b00;

	FLEXPWM_0.SUB[3].CTRL.B.LDFQ = 0b0000;
	FLEXPWM_0.SUB[3].CTRL.B.HALF = 1;
	FLEXPWM_0.SUB[3].CTRL.B.FULL = 1;
	FLEXPWM_0.SUB[3].CTRL.B.DT = 0b00;
	FLEXPWM_0.SUB[3].CTRL.B.PRSC = 0b000;
	FLEXPWM_0.SUB[3].CTRL.B.DBLEN = 0;

	FLEXPWM_0.SUB[3].OCTRL.B.PWMA_IN = 0;
	FLEXPWM_0.SUB[3].OCTRL.B.PWMB_IN = 0;
	FLEXPWM_0.SUB[3].OCTRL.B.PWMX_IN = 0;
	FLEXPWM_0.SUB[3].OCTRL.B.POLA = 0;
	FLEXPWM_0.SUB[3].OCTRL.B.POLB = 0;
	FLEXPWM_0.SUB[3].OCTRL.B.POLX = 0;
	FLEXPWM_0.SUB[3].OCTRL.B.PWMAFS = 0b00;
	FLEXPWM_0.SUB[3].OCTRL.B.PWMBFS = 0b00;
	FLEXPWM_0.SUB[3].OCTRL.B.PWMXFS = 0b00;

	FLEXPWM_0.SUB[3].DISMAP.B.DISX = 0b1111;
	FLEXPWM_0.SUB[3].DISMAP.B.DISB = 0b0000;
	FLEXPWM_0.SUB[3].DISMAP.B.DISA = 0b0000;

	FLEXPWM_0.SUB[3].DTCNT0.R = 0;
	FLEXPWM_0.SUB[3].DTCNT1.R = 0;


	/* SUB[3]******************************************************
	  FLEXPWM_0.SUB[3].INIT.R = 0xFFFF - 0x0C80 + 1;
	  FLEXPWM_0.SUB[3].VAL[0].R = 0;
	  FLEXPWM_0.SUB[3].VAL[1].R = 0x0C80;

	  FLEXPWM_0.SUB[3].CTRL2.R = 0x0000;
	  FLEXPWM_0.SUB[3].CTRL.R = 0x0C00;
	  FLEXPWM_0.SUB[3].OCTRL.R = 0x0000;
	  FLEXPWM_0.SUB[3].DISMAP.R = 0xFF00;

	  FLEXPWM_0.SUB[3].DTCNT0.R = 0;
	  FLEXPWM_0.SUB[3].DTCNT1.R = 0;

	 **************이 주석 처리 된 부분은 위에 초기화 세팅과 같은 역할을 합니다.********/
}

void PWM_OUT(void)
{
	FLEXPWM_0.SUB[3].VAL[2].R = (unsigned short) -PWM1_X;
	FLEXPWM_0.SUB[3].VAL[3].R = (unsigned short)  PWM1_X;

	/**********************************
    FLEXPWM_0.SUB[3].VAL[4].R = -PWM_X;
    FLEXPWM_0.SUB[3].VAL[5].R =  PWM_X;
    **** 3번 모듈 B채널을 사용하는데 이 부분이 주석 처리 된 이유는 대칭출력이기 때문에 따로 출력 설정을 하지 않아도 되서 입니다.
    주석 지우고 CTRL2에 INDEP 1로 셋팅 해보시면 확인 가능 합니다. */

	FLEXPWM_0.MCTRL.B.LDOK |= 0xF;  // PWM값을 load한다. load config values into buffers
	FLEXPWM_0.MCTRL.B.RUN |= 0xF;   // 1,2,3,4 Run
}


