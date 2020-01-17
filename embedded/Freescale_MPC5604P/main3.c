/*
 * freescale C ==> 이것저것 연습해본 코드. 제대로 동작하진 않는듯 ㅇㅇ..
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_sys.h"

vuint32_t i = 0;			    /* Dummy idle counter */
char LED1=1, LED2=2, LED3=1, LED4=1;
unsigned int Blank = 1000;
char cnt = 0;
char SW[4] = {0,0,0,0};
char SWold[4] = {0,0,0,0};
int LED[4];
int R_adc = 0;
vuint32_t Pit0cnt = 0;

void PIT0ISR()
{
	Pit0cnt++;
	PIT.CH[0].TFLG.B.TIF = 1;
}

/*
void Pit2ISR()
{
	Pit2Ctr++;
	Counter[2]++;

	if(Counter[2] >= Blank)
	{
		SIU.GPDO[55].B.PDO =~ SIU.GPDO[55].B.PDO;
		counter[2] = 0;
	}

	PIT.CH[2].TFLG.B.TIF = 1;
}
*/

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

	ADC_1.CTR[0].R = 0x00008208;

	ADC_1.NCMR[0].R = 0x00000020;
	
	ADC_1.CDR[5].R = 0x00000000;

	ADC_1.MCR.B.ABORT = 0;
}
/*
void PWM_out()
{
	FLEXPWM_0.SUB[0].VAL[2].R = (unsigned short)-PWM1_X;
	FLEXPWM_0.SUB[0].VAL[3].R = (unsigned short)-PWM1_X;
	FLEXPWM_0.SUB[1].VAL[2].R = (unsigned short)-PWM1_Y;
	FLEXPWM_0.SUB[1].VAL[3].R = (unsigned short)-PWM1_Y;
	FLEXPWM_0.SUB[2].VAL[2].R = (unsigned short)-PWM1_Z;
	FLEXPWM_0.SUB[2].VAL[3].R = (unsigned short)-PWM1_Z;

	FLEXPWM_0.MCTRL.B.LDOK |= 0xF;
	FLEXPWM_0.MCTRL.B.RUN |= 0xF;
}
*/

void Switch()
{
	SWold[0] = SW[0];
	SWold[1] = SW[1];
	SWold[2] = SW[2];
	SWold[3] = SW[3];

	SW[0] = SIU.GPDI[48].B.PDI;
	SW[1] = SIU.GPDI[49].B.PDI;
	SW[2] = SIU.GPDI[50].B.PDI;
	SW[3] = SIU.GPDI[51].B.PDI;

	if(!SWold[0] && SW[0]) 
	{
		cnt += 1;
	}
	if(!SWold[1] && SW[1]) 
	{
		cnt += 1;
	}
	if(!SWold[2] && SW[2]) 
	{
		cnt += 1;
	}
	if(!SWold[3] && SW[3]) 
	{
		cnt += 1;
	}
}

void LED_Ctr()
{
	SIU.GPDO[52].B.PDO = LED1;
	SIU.GPDO[53].B.PDO = LED2;
	SIU.GPDO[54].B.PDO = LED3;
	// SIU.GPDO[55].B.PDO = LED4;
}

void ADCRead_1()
{
	ADC_1.MCR.B.NSTART = 1;
	asm("nop");
	
	while(ADC_1.MCR.B.NSTART)
	{
		asm("nop");
	}
	R_adc = ADC_1.CDR[5].B.CDATA;

//	PWM1_X = (int)(R_adc * 3200.0 / 1024.0);
//	PWM1_Y = (int)(R_adc * 3200.0 / 1024.0);
//	PWM1_Z = (int)(R_adc * 3200.0 / 1024.0);
}

void init_PIT()
{
	PIT.PITMCR.R = 0x00000001;
	PIT.CH[0].LDVAL.R = 0x0061a800;
	PIT.CH[0].TCTRL.R = 0x00000003;
}

void main(void) 
{
    initModesAndClock(); 		
	disableWatchdog();    		
	enableIrq();		   		
//	initOutputClock();
	init_ADC1();
	init_PIT();
	INTC_InstallINTCInterruptHandler(PIT0ISR, 59, 6);
		
	init_INTC();				
	init_Linflex0();
	INTC.CPR.B.PRI = 0;
	FMSTR_Init();
	
	/* Loop forever */
	while(1) 
	{
		FMSTR_Recorder();
    	FMSTR_Poll();
    
    /*-----------------------------------*/
		//	SW_Func();
		LED_Ctr();	
		ADCRead_1();
		i++;
	}
}




