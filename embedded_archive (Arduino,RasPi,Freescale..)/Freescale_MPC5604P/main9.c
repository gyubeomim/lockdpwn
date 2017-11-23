/*
 * freescale C ==> flexpwm을 이용해 가변저항을 돌리면 PWM1_X,Y,Z, 값이 0 ~ 3200까지 변하는 코드
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_base.h"
#include "init_sys.h"

int i=0;
int R_adc =0;
int PWM1_X =0;
int PWM1_Y =0;
int PWM1_Z =0;

void init_ADC_1 (void);                //ADC 초기화            
void ADCRead_1(void);                  //ADC input
void init_FlexPWM0_GenConfig(void);    //PWM 설정
void PWM_out(void);

int main(void)
{
	initModesAndClock();
	disableWatchdog();
	enableIrq();
	
	FMSTR_Init();
	init_INTC();
	init_Linflex0();
	init_FlexPWM0_GenConfig();
	init_ADC_1();

	/// A[11] 포트에서 ALT2 기능인 A[0],FLEXPWM_0 기능을 사용한다 	
	SIU.PCR[11].R=0x0800;   //SUB[0]_PWM_FOWARD

	/// E[0] 포트에서 ALT 기능인 ADC_1을 사용하는 것 같다 
	/// APC(analog pad control) 기능을 ON으로 설정한다
	SIU.PCR[64]. R=0x2400;   //ADC input power limit

	//- Loop forever *-
	while(1)
	{
		FMSTR_Recorder();
		FMSTR_Poll();

		ADCRead_1();  // 가변저항을 돌리면
		PWM_out();   // 그 값을 읽어 3개의 PWM 신호가 발생한다
	}
}

// PWM1_X,Y,Z 신호를 발생시킨다
void PWM_out(void)
{
	// VAL[2]에는 X 파형을 반전시켜서 입력한다
	FLEXPWM_0.SUB[0].VAL[2].R = (unsigned short)-PWM1_X;
	FLEXPWM_0.SUB[0].VAL[3].R = (unsigned short)PWM1_X;
	FLEXPWM_0.SUB[1].VAL[2].R = (unsigned short)-PWM1_Y;
	FLEXPWM_0.SUB[1].VAL[3].R = (unsigned short)PWM1_Y;
	FLEXPWM_0.SUB[2].VAL[2].R = (unsigned short)-PWM1_Z;
	FLEXPWM_0.SUB[2].VAL[3].R = (unsigned short)PWM1_Z;

	FLEXPWM_0.MCTRL.B.LDOK |= 0xF;  // PWM값을 load한다. load config values into buffers
	FLEXPWM_0.MCTRL.B.RUN |= 0xF;   // 1,2,3,4 Run
}

// 가변저항 값을 읽는다
void ADCRead_1 (void)
{
	ADC_1.MCR.B.NSTART = 1; 
	asm("nop");
	
	while(ADC_1.MCR.B.NSTART) 
	{
		asm("nop");
	}

	if(ADC_1.CDR[5].B.VALID==1)
	{ 
		R_adc= ADC_1.CDR[5].B.CDATA; 
	}

	// PWM1 파형 값을 3200등분한다
	PWM1_X = (int)(R_adc * 3200.0 / 1024.0);
	PWM1_Y = (int)(R_adc * 3200.0 / 1024.0);
	PWM1_Z = (int)(R_adc * 3200.0 / 1024.0);
}

void init_ADC_1(void)
{
	ADC_1.MCR.B.ABORT =1;
	ADC_1.MCR.B.WLSIDE =0;
	ADC_1.MCR.B.MODE =0;
	ADC_1.MCR.B.ADCLKSEL =1;
	ADC_1.MCR.B.PWDN =0;

	ADC_1.CTR[0].R = 0x00008208;   // 0000 0000 0000 0000 1000 0010 0000 1000
	// Phase Duration Latch(INPLATCH) : Enabled(Always) 	1 clock Cycle
	// Input Sampling Duration(INPSAMP) : 8 (INPSAMP >= 8) 	7 clock Cycles
	// Input Comparison Duration(INPCMP) : 0b01 			12 clock Cycles
	// Conversion Time : 7 + 12 + 1 (Tck) 					20 clock Cycles 

	ADC_1.NCMR[0].R = 0x00000020; // Select ANS5 Inputs for conversion
	ADC_1.CDR[5].R = 0x00000000; // Channel[5] Set Default
	ADC_1.MCR.B.ABORT = 0; // 
}

void init_FlexPWM0_GenConfig(void)
{
	//-----------------------------------------------------------
	//    FlexPWM General Configuration Initialization code for FLEXPWM_0 Device
	//-----------------------------------------------------------
	FLEXPWM_0.OUTEN.B.PWMA_EN = 0b0011; // PWM A Output Enable submodule 0:2
	FLEXPWM_0.OUTEN.B.PWMB_EN = 0b0010; // PWM B Output Enabled Submodule 0:2
	FLEXPWM_0.OUTEN.B.PWMX_EN = 0b0000;  // PWM X Output Disable

	// Mask 설정시 PWM값을 강제로 0으로 만든다
	FLEXPWM_0.MASK.R = 0x0000;    // PWM All Mask Disable

	FLEXPWM_0.SWCOUT.B.OUTA_3 = 0;   // S/W Controlled O/P OUTA_3 Disable
	FLEXPWM_0.SWCOUT.B.OUTB_3 = 0;   // S/W Controlled O/P OUTB_3 Disable
	FLEXPWM_0.SWCOUT.B.OUTA_2 = 1;   // S/W Controlled O/P OUTA_2 Enable
	FLEXPWM_0.SWCOUT.B.OUTB_2 = 1;   // S/W Controlled O/P OUTB_2 Enable
	FLEXPWM_0.SWCOUT.B.OUTA_1 = 1;   // S/W Controlled O/P OUTA_1 Enable
	FLEXPWM_0.SWCOUT.B.OUTB_1 = 1;   // S/W Controlled O/P OUTB_1 Enable
	FLEXPWM_0.SWCOUT.B.OUTA_0 = 1;   // S/W Controlled O/P OUTA_0 Enable
	FLEXPWM_0.SWCOUT.B.OUTB_0 = 1;   // S/W Controlled O/P OUTB_0 Enable

	FLEXPWM_0.DTSRCSEL.R = 0x0000;   // Deadtime source : Generated PWM signal is used by the deadtime logic.
	FLEXPWM_0.FCTRL.R = 0x0000;
	FLEXPWM_0.FFILT.R = 0x0000;
	FLEXPWM_0.MCTRL.R = 0x0000;
}




