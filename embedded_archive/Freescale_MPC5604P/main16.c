/*
 *	freescale c ==> 가변저항 돌리면 LED 밝기가 PWM값에 따라 달라지는 코드
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_base.h"

/************ Vari ***********/
volatile int i = 0, Pit0cnt = 0;
char n = 0;
int  R_adc = 0;
int PWM_X = 0;

void init_PIT(void)
{
	PIT.PITMCR.R = 0x00000000;
	PIT.CH[0].LDVAL.R = 0x03D09000;
	PIT.CH[0].TCTRL.R = 0x00000003;
}

void PIT0ISR(void)
{ 
	PWM_X += 100;
	if(PWM_X>=3199) PWM_X = 0;

	Pit0cnt++;
	PIT.CH[0].TFLG.B.TIF = 1;
}

void init_PWM(void)
{
	FLEXPWM_0.OUTEN.B.PWMA_EN = 0b1000; // PWM 모듈 3번  사용 하는 겁니다.
	FLEXPWM_0.OUTEN.B.PWMB_EN = 0b1000;
	FLEXPWM_0.OUTEN.B.PWMX_EN = 0b0000;

	FLEXPWM_0.MASK.R = 0x0000;

	FLEXPWM_0.SWCOUT.R = 0x00ff;

	FLEXPWM_0.SUB[3].INIT.R = 0xffff - 0x0C80 + 1;
	FLEXPWM_0.SUB[3].VAL[0].R = 0;
	FLEXPWM_0.SUB[3].VAL[1].R = 0x0C80;

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


	/*********SUB[3]*******************************************************************
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

void PWM(void)
{
	FLEXPWM_0.SUB[3].VAL[2].R = (unsigned short)-PWM_X;
	FLEXPWM_0.SUB[3].VAL[3].R =  (unsigned short)PWM_X;


	/**********************************
	  FLEXPWM_0.SUB[3].VAL[4].R = -PWM_X;
	  FLEXPWM_0.SUB[3].VAL[5].R =  PWM_X;
	 **** 3번 모듈 B채널을 사용하는데 이 부분이 주석 처리 된 이유는 대칭출력이기 때문에 따로 출력 설정을 하지 않아도 되서 입니다.
	 주석 지우고 CTRL2에 INDEP 1로 셋팅 해보시면 확인 가능 합니다. */


	FLEXPWM_0.MCTRL.B.LDOK = 0xF;
	FLEXPWM_0.MCTRL.B.RUN  = 0xF;
}

void init_ADC(void)
{
	ADC_1.MCR.B.ABORT = 1;

	ADC_1.MCR.B.OWREN = 0;
	ADC_1.MCR.B.WLSIDE = 0;
	ADC_1.MCR.B.MODE = 0;
	ADC_1.MCR.B.CTUEN = 0;
	ADC_1.MCR.B.ADCLKSEL = 0;
	ADC_1.MCR.B.ACK0 = 0;
	ADC_1.MCR.B.PWDN = 0;

	ADC_1.CTR[0].R = 0x00008208;
	ADC_1.NCMR[0].R = 0x00000020;
	ADC_1.CDR[5].R = 0x00000000;
	ADC_1.MCR.B.ABORT = 0;
}

void ADCRead_1(void)
{
	ADC_1.MCR.B.NSTART = 1;
	asm("nop");

	while(ADC_1.MCR.B.NSTART) asm("nop");
	R_adc = ADC_1.CDR[5].B.CDATA;
	
	PWM_X = (int)(R_adc * 3200.0 / 1024.0);
}

int main(void)
{
	initModesAndClock();
	disableWatchdog();
	enableIrq();
	//initOutputClock();
	FMSTR_Init();
	init_INTC();
	init_Linflex0();
	//init_PIT();
	//INTC_InstallINTCInterruptHandler(PIT0ISR,59,6);
	init_PWM();
	init_ADC();

	SIU.PCR[52].R = 0x0C00;  //52번 핀 PWM B[3] 사용
	SIU.PCR[64].R = 0x2400;   //ADC input power limit 
							 /// E[0] 포트에서 ALT 기능인 ADC_1을 사용하는 것 같다 
							 /// APC(analog pad control) 기능을 ON으로 설정한다
	/* Loop forever */
	for (;;) 
	{
		FMSTR_Recorder();
		FMSTR_Poll();
		ADCRead_1();
		PWM();
	}
}

