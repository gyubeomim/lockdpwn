/*
 *	freescale c ==> 라인트레이서 코드
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_base.h"

int servoControl = 0;
int motorControl = 0;
int R_adc = 0;

struct SENSOR
{
	union
	{
		vuint8_t R;
		struct
		{
          vuint8_t :4;
		  vuint8_t sensor1:1;
		  vuint8_t sensor2:1;
		  vuint8_t sensor3:1;
		  vuint8_t sensor4:1;
		}B;
	}sen;
};

struct SENSOR tracesensor;

void sensor(void)
{
	tracesensor.sen.B.sensor1 = SIU.GPDI[44].B.PDI;
	tracesensor.sen.B.sensor2 = SIU.GPDI[45].B.PDI;
	tracesensor.sen.B.sensor3 = SIU.GPDI[46].B.PDI;
	tracesensor.sen.B.sensor4 = SIU.GPDI[47].B.PDI;
}

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
	motorControl = R_adc / 128;
}

void init_FlexPWM0_GenConfig(void) // 모터 초기화 코드
{
//-----------------------------------------------------------
//    FlexPWM General Configuration Initialization code for FLEXPWM_0 Device
//-----------------------------------------------------------
	FLEXPWM_0.OUTEN.B.PWMA_EN = 0b0011;		// PWM A Output Enabled Submodule 0:2
	FLEXPWM_0.OUTEN.B.PWMB_EN = 0b0010;		// PWM B Output Enabled Submodule 0:2
	FLEXPWM_0.OUTEN.B.PWMX_EN = 0b0000;		// PWM X Output Disable
	
	FLEXPWM_0.MASK.R = 0x0000;				// PWM All Mask Disable
	
	FLEXPWM_0.SWCOUT.B.OUTA_3 = 0;			// S/W Controlled O/P OUTA_3 Disable
	FLEXPWM_0.SWCOUT.B.OUTB_3 = 0;			// S/W Controlled O/P OUTB_3 Disable
	FLEXPWM_0.SWCOUT.B.OUTA_2 = 1;			// S/W Controlled O/P OUTA_2 Enable
	FLEXPWM_0.SWCOUT.B.OUTB_2 = 1;			// S/W Controlled O/P OUTB_2 Enable
	FLEXPWM_0.SWCOUT.B.OUTA_1 = 1;			// S/W Controlled O/P OUTA_1 Enable
	FLEXPWM_0.SWCOUT.B.OUTB_1 = 1;			// S/W Controlled O/P OUTB_1 Enable
	FLEXPWM_0.SWCOUT.B.OUTA_0 = 1;			// S/W Controlled O/P OUTA_0 Enable
	FLEXPWM_0.SWCOUT.B.OUTB_0 = 1;			// S/W Controlled O/P OUTB_0 Enable
	
	FLEXPWM_0.DTSRCSEL.R = 0x0000;			// Deadtime source : Generated PWM signal is used by the deadtime logic.
	FLEXPWM_0.FCTRL.R = 0x0000;
	FLEXPWM_0.FFILT.R = 0x0000;
	FLEXPWM_0.MCTRL.R = 0x0000;
}

void init_FlexPWM0_sub0(void) // SERVO MOTOR 제어를 위해 0번 모튤 초기화
{
//-----------------------------------------------------------------------
//     FlexPWM Submodule0 Configuration Initialization code for FLEXPWM_0 Device
//-----------------------------------------------------------------------
    /*PWM SUB[0] setting 200Hz survo*/
	FLEXPWM_0.SUB[0].INIT.R = 0xffff - 0x09c4 + 1;
	FLEXPWM_0.SUB[0].VAL[0].R = 0;
	FLEXPWM_0.SUB[0].VAL[1].R = 0x09c4;

	FLEXPWM_0.SUB[0].CTRL2.B.DBGEN		= 0;		// Debug Enable : Disable
	FLEXPWM_0.SUB[0].CTRL2.B.WAITEN		= 0;		// Wait Enable : Disable
	FLEXPWM_0.SUB[0].CTRL2.B.INDEP		= 1;		// Pair Operation : Independent
	FLEXPWM_0.SUB[0].CTRL2.B.PWMA_INIT	= 0;		// PWMA Initial Value : 0
	FLEXPWM_0.SUB[0].CTRL2.B.PWMB_INIT	= 0;		// PWMB Initial Value : 0
	FLEXPWM_0.SUB[0].CTRL2.B.PWMX_INIT	= 0;		// PWMX Initial Value : 0
	FLEXPWM_0.SUB[0].CTRL2.B.INIT_SEL	= 0b00;		// Initialization Control : Local sync
	FLEXPWM_0.SUB[0].CTRL2.B.FRCEN		= 0;		// Force out event Initialization : Disable
	FLEXPWM_0.SUB[0].CTRL2.B.FORCE		= 0;		// Force Initialization : Disable
	FLEXPWM_0.SUB[0].CTRL2.B.FORCE_SEL	= 0b000;	// Force Source : Local force
	FLEXPWM_0.SUB[0].CTRL2.B.RELOAD_SEL	= 0;		// Reload Source : Local
	FLEXPWM_0.SUB[0].CTRL2.B.CLK_SEL	= 0b00;		// Clock Source : IPBus clock

    FLEXPWM_0.SUB[0].CTRL.B.LDFQ  = 0b0000;			// Load Frequency : Every PWM
	FLEXPWM_0.SUB[0].CTRL.B.HALF  = 1;				// Half Cycle Reload : Enable
	FLEXPWM_0.SUB[0].CTRL.B.FULL  = 1;				// Full Cycle Reload : Enable
	FLEXPWM_0.SUB[0].CTRL.B.DT    = 0b00;			// Deadtime from PWMX(DT[0], DT[1]) : None
	FLEXPWM_0.SUB[0].CTRL.B.PRSC  = 0b110;			// Prescaler : clk / 64
	FLEXPWM_0.SUB[0].CTRL.B.DBLEN = 0;				// Double Switching : Disable

	FLEXPWM_0.SUB[0].OCTRL.B.PWMA_IN = 0;		// PWM A Input Logic Value
	FLEXPWM_0.SUB[0].OCTRL.B.PWMB_IN = 0;		// PWM B Input Logic Value
	FLEXPWM_0.SUB[0].OCTRL.B.PWMX_IN = 0;		// PWM X Input Logic Value
	FLEXPWM_0.SUB[0].OCTRL.B.POLA    = 0;		// PWM A Output Polarity : PWMA output not Inverted  // 반전시켜준다.
	FLEXPWM_0.SUB[0].OCTRL.B.POLB    = 0;		// PWM B Output Polarity : PWMB output not Inverted  // 반전시켜준다.
	FLEXPWM_0.SUB[0].OCTRL.B.POLX    = 0;		// PWM X Output Polarity : PWMX output not Inverted  // 반전시켜준다.
	FLEXPWM_0.SUB[0].OCTRL.B.PWMAFS  = 0b00;	// PWM A Fault State : Output is forced to logic 0
	FLEXPWM_0.SUB[0].OCTRL.B.PWMBFS  = 0b00;	// PWM B Fault State : Output is forced to logic 0
	FLEXPWM_0.SUB[0].OCTRL.B.PWMXFS  = 0b00;	// PWM X Fault State : Output is forced to logic 0
	
	FLEXPWM_0.SUB[0].DISMAP.B.DISX = 0b1111;	// PWM X Fault Mask : Turn off
	FLEXPWM_0.SUB[0].DISMAP.B.DISB = 0b0000;	// PWM B Fault Mask : Turn on
	FLEXPWM_0.SUB[0].DISMAP.B.DISA = 0b0000;	// PWM A Fault Mask : Turn on
    
	FLEXPWM_0.SUB[0].DTCNT0.R = 0;		// PWM A Deadtime Count
	FLEXPWM_0.SUB[0].DTCNT1.R = 0;		// PWM B Deadtime Count
}

void init_FlexPWM0_sub1(void) // DC MOTOR 제어를 위해 1번 모듈 초기화
{
//-----------------------------------------------------------------------
//     FlexPWM Submodule0 Configuration Initialization code for FLEXPWM_1 Device
//-----------------------------------------------------------------------
    /*PWM SUB[1] setting 200Hz survo*/
	FLEXPWM_0.SUB[1].INIT.R = 0xffff - 0x09c4 + 1;
	FLEXPWM_0.SUB[1].VAL[0].R = 0;
	FLEXPWM_0.SUB[1].VAL[1].R = 0x09c4;

	FLEXPWM_0.SUB[1].CTRL2.B.DBGEN		= 0;		// Debug Enable : Disable
	FLEXPWM_0.SUB[1].CTRL2.B.WAITEN		= 0;		// Wait Enable : Disable
	FLEXPWM_0.SUB[1].CTRL2.B.INDEP		= 1;		// Pair Operation : Independent
	FLEXPWM_0.SUB[1].CTRL2.B.PWMA_INIT	= 0;		// PWMA Initial Value : 0
	FLEXPWM_0.SUB[1].CTRL2.B.PWMB_INIT	= 0;		// PWMB Initial Value : 0
	FLEXPWM_0.SUB[1].CTRL2.B.PWMX_INIT	= 0;		// PWMX Initial Value : 0
	FLEXPWM_0.SUB[1].CTRL2.B.INIT_SEL	= 0b00;		// Initialization Control : Local sync
	FLEXPWM_0.SUB[1].CTRL2.B.FRCEN		= 0;		// Force out event Initialization : Disable
	FLEXPWM_0.SUB[1].CTRL2.B.FORCE		= 0;		// Force Initialization : Disable
	FLEXPWM_0.SUB[1].CTRL2.B.FORCE_SEL	= 0b000;	// Force Source : Local force
	FLEXPWM_0.SUB[1].CTRL2.B.RELOAD_SEL	= 0;		// Reload Source : Local
	FLEXPWM_0.SUB[1].CTRL2.B.CLK_SEL	= 0b00;		// Clock Source : IPBus clock

    FLEXPWM_0.SUB[1].CTRL.B.LDFQ  = 0b0000;			// Load Frequency : Every PWM
	FLEXPWM_0.SUB[1].CTRL.B.HALF  = 1;				// Half Cycle Reload : Enable
	FLEXPWM_0.SUB[1].CTRL.B.FULL  = 1;				// Full Cycle Reload : Enable
	FLEXPWM_0.SUB[1].CTRL.B.DT    = 0b00;			// Deadtime from PWMX(DT[0], DT[1]) : None
	FLEXPWM_0.SUB[1].CTRL.B.PRSC  = 0b110;			// Prescaler : clk / 64
	FLEXPWM_0.SUB[1].CTRL.B.DBLEN = 0;				// Double Switching : Disable

	FLEXPWM_0.SUB[1].OCTRL.B.PWMA_IN = 0;		// PWM A Input Logic Value
	FLEXPWM_0.SUB[1].OCTRL.B.PWMB_IN = 0;		// PWM B Input Logic Value
	FLEXPWM_0.SUB[1].OCTRL.B.PWMX_IN = 0;		// PWM X Input Logic Value
	FLEXPWM_0.SUB[1].OCTRL.B.POLA    = 0;		// PWM A Output Polarity : PWMA output not Inverted  // 반전시켜준다.
	FLEXPWM_0.SUB[1].OCTRL.B.POLB    = 0;		// PWM B Output Polarity : PWMB output not Inverted  // 반전시켜준다.
	FLEXPWM_0.SUB[1].OCTRL.B.POLX    = 0;		// PWM X Output Polarity : PWMX output not Inverted  // 반전시켜준다.
	FLEXPWM_0.SUB[1].OCTRL.B.PWMAFS  = 0b00;	// PWM A Fault State : Output is forced to logic 0
	FLEXPWM_0.SUB[1].OCTRL.B.PWMBFS  = 0b00;	// PWM B Fault State : Output is forced to logic 0
	FLEXPWM_0.SUB[1].OCTRL.B.PWMXFS  = 0b00;	// PWM X Fault State : Output is forced to logic 0
	
	FLEXPWM_0.SUB[1].DISMAP.B.DISX = 0b1111;	// PWM X Fault Mask : Turn off
	FLEXPWM_0.SUB[1].DISMAP.B.DISB = 0b0000;	// PWM B Fault Mask : Turn on
	FLEXPWM_0.SUB[1].DISMAP.B.DISA = 0b0000;	// PWM A Fault Mask : Turn on
    
	FLEXPWM_0.SUB[1].DTCNT0.R = 0;		// PWM A Deadtime Count
	FLEXPWM_0.SUB[1].DTCNT1.R = 0;		// PWM B Deadtime Count
}

void lineTracerTest()
{
	switch(tracesensor.sen.R)
	{
		case 0b0000:
			servoControl = 200;
			break;
		case 0b0111:
			servoControl = 300;
			break;
		case 0b0011:
			servoControl = 400;
			break;
	}
	
	FLEXPWM_0.SUB[0].VAL[2].R = (unsigned short) - servoControl;
	FLEXPWM_0.SUB[0].VAL[3].R = (unsigned short)  servoControl;
	
	FLEXPWM_0.SUB[1].VAL[2].R = (unsigned short) - motorControl;
	FLEXPWM_0.SUB[1].VAL[3].R = (unsigned short)  motorControl;

	FLEXPWM_0.MCTRL.B.LDOK |= 0xf;
	FLEXPWM_0.MCTRL.B.RUN |= 0xf;
}

int main(void)
{
	initModesAndClock();
	disableWatchdog();
	enableIrq();
	FMSTR_Init();
	init_INTC();	   		
	init_Linflex0();
	INTC.CPR.B.PRI = 0;

	init_FlexPWM0_GenConfig();
	init_FlexPWM0_sub0();
	init_FlexPWM0_sub1();
	init_ADC1();

	// 적외선센서 4개 초기화 코드
	SIU.PCR[44].R = 0x0100;  // Sensor1 C[12] PWM1A
	SIU.PCR[45].R = 0x0100;  // Sensor1 C[13] PWM1B
	SIU.PCR[46].R = 0x0100;  // Sensor1 C[14] PWM2A
	SIU.PCR[47].R = 0x0100;  // Sensor1 C[15] PWM2B

	SIU.PCR[58].R = 0x0600; // PD10 : PWM A[0] SURVO
	SIU.PCR[61].R = 0x0600; // PD13 : PWM A[1] DC

	SIU.PCR[64].R = 0x2400;  // E0 포트 설정 (ADC_1 가변저항 파란색 움직이는거 사용한다고 선언)

	/* Loop forever */
	while(1)
	{
		FMSTR_Recorder();
		FMSTR_Poll();

		sensor();
		lineTracerTest();
		ADCRead_1();
	}
}




