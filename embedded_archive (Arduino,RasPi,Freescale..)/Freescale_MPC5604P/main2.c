/*
 * freescale C ==> 상진킴이 준 코드. 라인트레이서용 코드인듯 
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_base.h"
#include "init_sys.h"

int i=0;
int R_adc =0;
int spdgain=0;

unsigned short pwm = 0;
unsigned short SERVOpwm=0;
unsigned short DCpwm=0;

void init_ADC_1 (void);                //ADC 초기화            
void ADCRead_1(void);                  //ADC input
void init_FlexPWM0_GenConfig(void);    //PWM 설정
void init_FlexPWM0_sub1(void);         //PWM 설정- submodule[1]
void init_FlexPWM0_sub0(void);         //PWM 설정- submodule[0]
void DC_MOTOR(void);
void SERVO_MOTOR(void);

union
{
	vuint8_t R;
	
	struct 
	{
vuint8_t :4;
		  vuint8_t SENSOR1 :1;
		  vuint8_t SENSOR2 :1;
		  vuint8_t SENSOR3 :1;
		  vuint8_t SENSOR4 :1;
	}B;
}SENSOR;

int main(void)
{
	initModesAndClock();
	disableWatchdog();
	enableIrq();
	
	initOutputClock();
	
	FMSTR_Init();
	init_INTC();
	init_Linflex0();
	init_FlexPWM0_GenConfig();
	init_FlexPWM0_sub0();
	init_FlexPWM0_sub1();
	init_ADC_1();

	/// A[11] 포트에서 ALT2 기능인 A[0],FLEXPWM_0 기능을 사용한다 	
	SIU.PCR[11]. R=0x0800;   //SUB[0]_PWM_FOWARD
	
	///	OUTPUT으로 설정
	SIU.PCR[40]. R=0x0200;   // MOTOR_DRIVE_ENABLE_PIN_C[8] 	
	
	/// C[7]포트에서 ALT2 기능인 A[1], FLEXPWM_0 기능을 사용한다
	SIU.PCR[39]. R=0x0800;   // SUB[1]_PWMA_OUTPUT_PIN_C[7] 
	/// C[6]포트에서 ALT2 기능인 B[1], FLEXPWM_0 기능을 사용한다
	SIU.PCR[38]. R=0x0800;   // SUB[1]_PWMB_OUTPUT_PIN_C[6]

	SIU.PCR[32]. R=0x0100;   // sensor1 C[0]
	SIU.PCR[33]. R=0x0100;   // sensor2 C[1]
	SIU.PCR[34]. R=0x0100;   // sensor3 C[2]
	SIU.PCR[35]. R=0x0100;   // sensor4 C[3]
	
	/// E[0] 포트에서 ALT 기능인 ADC_1을 사용하는 것 같다 
	/// APC(analog pad control) 기능을 ON으로 설정한다
	SIU.PCR[64]. R=0x2400;   //ADC input power limit

	//- Loop forever *-
	while(1)
	{
		FMSTR_Recorder();
		FMSTR_Poll();

		SIU.GPDO[40].B.PDO=1; 	// DCmotor Enable
		SENSOR.B.SENSOR1 = SIU.GPDI[32].B.PDI;  //sensor1
		SENSOR.B.SENSOR2 = SIU.GPDI[33].B.PDI;  //sensor2
		SENSOR.B.SENSOR3 = SIU.GPDI[34].B.PDI;  //sensor3
		SENSOR.B.SENSOR4 = SIU.GPDI[35].B.PDI;  //sensor4
		ADCRead_1();

		switch(SENSOR.R)
		{
			case 0b0111:
				SERVOpwm = 310;  //300
				spdgain= 60;
				break;

			case 0b0011:
				SERVOpwm = 320;  //320
				spdgain= 70;
				break;

			case 0b0001:
				SERVOpwm = 340;
				spdgain= 90;
				break;

			case 0b1001:
				SERVOpwm = 375;
				spdgain= 100;
				break;

			case 0b1000:
				SERVOpwm = 410;
				spdgain= 90;
				break;

			case 0b1100:
				SERVOpwm = 440;  //430
				spdgain= 70;
				break;

			case 0b1110:
				SERVOpwm = 450;  //450
				spdgain= 60;
				break;

			case 0b1111:
				SERVOpwm = 300;  //450
				spdgain= 100;
				break;
		}
		SERVO_MOTOR();
		DC_MOTOR();

		i++;
	}
}

void SERVO_MOTOR(void)
{
	// VAL[2]는 SERVOpwm 값을 반전시켜서 입력한다
	FLEXPWM_0.SUB[0].VAL[2].R = -SERVOpwm;
	FLEXPWM_0.SUB[0].VAL[3].R = SERVOpwm;

	FLEXPWM_0.MCTRL.B.LDOK |= 0xF;  // PWM값을 load한다. load config values into buffers
	FLEXPWM_0.MCTRL.B.RUN |= 0xF;   // 1,2,3,4 Run
}

void DC_MOTOR(void)
{
	DCpwm = spdgain*(R_adc*32)/1024;

	FLEXPWM_0.SUB[1].VAL[2].R= -DCpwm;
	FLEXPWM_0.SUB[1].VAL[3].R= DCpwm;

	FLEXPWM_0.MCTRL.B.LDOK |=0XF;   // load config values into buffers
	FLEXPWM_0.MCTRL.B.RUN |=0XF;    // 1,2,3,4 Run
}

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
}

void init_ADC_1(void)
{
	ADC_1.MCR.B.ABORT =1;
	ADC_1.MCR.B.WLSIDE =0;
	ADC_1.MCR.B.MODE =0;
	ADC_1.MCR.B.ADCLKSEL =1;
	ADC_1.MCR.B.PWDN =0;

	ADC_1.CTR[0].R = 0x00008208;
	ADC_1.NCMR[0].R = 0x0000020;
	ADC_1.CDR [5].R = 0x00000000;
	ADC_1.MCR. B. ABORT = 0;
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

void init_FlexPWM0_sub1(void)
{
	//-----------------------------------------------------------------------
	//     FlexPWM Submodule0 Configuration Initialization code for FLEXPWM_0 Device
	//-----------------------------------------------------------------------
	FLEXPWM_0.SUB[1].INIT.R = 0xffff-0x0C80+1; //62336 in 10kHz,63936 in 20kHz
	FLEXPWM_0.SUB[1].CTRL2.B.DBGEN  = 1;  // Debug Enable : Enable
	FLEXPWM_0.SUB[1].CTRL2.B.WAITEN  = 1;  // Wait Enable : Disable
	FLEXPWM_0.SUB[1].CTRL2.B.INDEP  = 1;  // Pair Operation : Independent
	//  FLEXPWM_0.SUB[1].CTRL2.B.PWMA_INIT = 0;  // PWMA Initial Value : 0
	// FLEXPWM_0.SUB[1].CTRL2.B.PWMB_INIT = 0;  // PWMB Initial Value : 0
	// FLEXPWM_0.SUB[1].CTRL2.B.PWMX_INIT = 0;  // PWMX Initial Value : 0
	// FLEXPWM_0.SUB[1].CTRL2.B.INIT_SEL = 0b00;  // Initialization Control : Local sync
	// FLEXPWM_0.SUB[1].CTRL2.B.FRCEN  = 0;  // Force out event Initialization : Disable
	// FLEXPWM_0.SUB[1].CTRL2.B.FORCE  = 0;  // Force Initialization : Disable
	// FLEXPWM_0.SUB[1].CTRL2.B.FORCE_SEL = 0b000; // Force Source : Local force
	// FLEXPWM_0.SUB[1].CTRL2.B.RELOAD_SEL = 0;  // Reload Source : Local
	// FLEXPWM_0.SUB[1].CTRL2.B.CLK_SEL = 0b00;  // Clock Source : IPBus clock
	//
	//  FLEXPWM_0.SUB[1].CTRL.B.LDFQ  = 0b0000;   // Load Frequency : Every PWM
	FLEXPWM_0.SUB[1].CTRL.B.HALF  = 1;    // Half Cycle Reload : Enable
	FLEXPWM_0.SUB[1].CTRL.B.FULL  = 1;    // Full Cycle Reload : Enable
	// FLEXPWM_0.SUB[1].CTRL.B.DT    = 0b00;   // Deadtime from PWMX(DT[0], DT[1]) : None
	FLEXPWM_0.SUB[1].CTRL.B.PRSC  = 0b0000;   // Prescaler : fclk
	// FLEXPWM_0.SUB[1].CTRL.B.DBLEN = 0;    // Double Switching : Disable
	FLEXPWM_0.SUB[1].VAL[0].R = 0x0000;       //Mid-cycle Reload Point for the PWM in PWM clock periods
	FLEXPWM_0.SUB[1].VAL[1].R = 0x0C80; //0x0c80; // Modulo(Maximum) Count Value for the submodule counter
	// FLEXPWM_0.SUB[1].VAL[2].R = 0x0000;      // Count value to set PWMA high
	// FLEXPWM_0.SUB[1].VAL[3].R = 0x0000;      // Count value to set PWMA low
	// FLEXPWM_0.SUB[1].VAL[4].R = 0x0000;      // Count value to set PWMB high
	// FLEXPWM_0.SUB[1].VAL[5].R = 0x0000;      // Count value to set PWMB low
	// FLEXPWM_0.SUB[1].OCTRL.B.PWMA_IN = 0;  // PWM A Input Logic Value
	// FLEXPWM_0.SUB[1].OCTRL.B.PWMB_IN = 0;  // PWM B Input Logic Value
	// FLEXPWM_0.SUB[1].OCTRL.B.PWMX_IN = 0;  // PWM X Input Logic Value
	// FLEXPWM_0.SUB[1].OCTRL.B.POLA    = 0;  // PWM A Output Polarity : PWMA output not Inverted  // 반전시켜준다.
	// FLEXPWM_0.SUB[1].OCTRL.B.POLB    = 0;  // PWM B Output Polarity : PWMB output not Inverted  // 반전시켜준다.
	// FLEXPWM_0.SUB[1].OCTRL.B.POLX    = 0;  // PWM X Output Polarity : PWMX output not Inverted  // 반전시켜준다.
	// FLEXPWM_0.SUB[1].OCTRL.B.PWMAFS  = 0b00; // PWM A Fault State : Output is forced to logic 0
	// FLEXPWM_0.SUB[1].OCTRL.B.PWMBFS  = 0b00; // PWM B Fault State : Output is forced to logic 0
	// FLEXPWM_0.SUB[1].OCTRL.B.PWMXFS  = 0b00; // PWM X Fault State : Output is forced to logic 0
	//
	FLEXPWM_0.SUB[1].TCTRL.R = 0x0004;   // Output Trigger Control Register
	// FLEXPWM_0.SUB[1].INTEN.R = 0x0000; //0x0003; // Interrupt Enable Register  1 : single sampling
	//            //        3 : double sampling
	// FLEXPWM_0.SUB[1].DMAEN.R = 0x0000;

	FLEXPWM_0.SUB[1].DISMAP.B.DISX = 0b1111; // PWM X Fault Mask : Turn off
	FLEXPWM_0.SUB[1].DISMAP.B.DISB = 0b0000; // PWM B Fault Mask : Turn on
	FLEXPWM_0.SUB[1].DISMAP.B.DISA = 0b0000; // PWM A Fault Mask : Turn on
	// FLEXPWM_0.SUB[1].DTCNT0.R = DTIME_CLOCK_PERIOD;  // PWM A Deadtime Count
	// FLEXPWM_0.SUB[1].DTCNT1.R = DTIME_CLOCK_PERIOD;  // PWM B Deadtime Count
	// FLEXPWM_0.SUB[1].DTCNT0.R = 0;  // PWM A Deadtime Count
	// FLEXPWM_0.SUB[1].DTCNT1.R = 0;  // PWM B Deadtime Count
	// FLEXPWM_0.SUB[1].CAPTCTRLX.R = 0x0000;
	// FLEXPWM_0.SUB[1].CAPTCOMPX.R = 0x0000;
}

void init_FlexPWM0_sub0(void)
{
	//-----------------------------------------------------------------------
	//     FlexPWM Submodule0 Configuration Initialization code for FLEXPWM_0 Device
	//-----------------------------------------------------------------------
	FLEXPWM_0.SUB[0].INIT.R = 0xffff-0x1046+1; //62336 in 10kHz, 63936 in 20kHz // PWM count 초기값
	// PWM 세부 설정
	FLEXPWM_0.SUB[0].CTRL2.B.DBGEN  = 1;  // Debug Enable : Disable 
	FLEXPWM_0.SUB[0].CTRL2.B.WAITEN  = 1;  // Wait Enable : Disable
	FLEXPWM_0.SUB[0].CTRL2.B.INDEP  = 1;  // Pair Operation : Independent 
										  // PWM파를 대칭적으로 발생시킬 때 사용한다
	//- FLEXPWM_0.SUB[0].CTRL2.B.PWMA_INIT = 0;  // PWMA Initial Value : 0
	FLEXPWM_0.SUB[0].CTRL2.B.PWMB_INIT = 0;  // PWMB Initial Value : 0
	FLEXPWM_0.SUB[0].CTRL2.B.PWMX_INIT = 0;  // PWMX Initial Value : 0
	FLEXPWM_0.SUB[0].CTRL2.B.INIT_SEL = 0b00;  // Initialization Control : Local sync
	FLEXPWM_0.SUB[0].CTRL2.B.FRCEN  = 0;  // Force out event Initialization : Disable
	FLEXPWM_0.SUB[0].CTRL2.B.FORCE  = 0;  // Force Initialization : Disable
	FLEXPWM_0.SUB[0].CTRL2.B.FORCE_SEL = 0b000; // Force Source : Local force
	FLEXPWM_0.SUB[0].CTRL2.B.RELOAD_SEL = 0;  // Reload Source : Local
	FLEXPWM_0.SUB[0].CTRL2.B.CLK_SEL = 0b00;  // Clock Source : IPBus clock
	FLEXPWM_0.SUB[0].CTRL.B.LDFQ  = 0b0000;   // Load Frequency : Every PWM
		   									 //  Load Frequency 설정 매 PWM마다 로딩을한다
											 //  내가 준 VAL[0],[1],[2] 값을 매 PWM파가 시작할 때마다 로딩하라는 뜻인듯. 즉각즉간 로딩해야 바로 신호를 읽을 수 있다 
	FLEXPWM_0.SUB[0].CTRL.B.HALF  = 1;    // Half Cycle Reload : Enable
	FLEXPWM_0.SUB[0].CTRL.B.FULL  = 1;    // Full Cycle Reload : Enable
	// FLEXPWM_0.SUB[0].CTRL.B.DT    = 0b00;   // Deadtime from PWMX(DT[0], DT[1]) : None
	FLEXPWM_0.SUB[0].CTRL.B.PRSC  = 0b111;   // Prescaler : fclk
	// FLEXPWM_0.SUB[0].CTRL.B.DBLEN = 0;    // Double Switching : Disable
	FLEXPWM_0.SUB[0].VAL[0].R = 0x0000;       //Mid-cycle Reload Point for the PWM in PWM clock periods  // PWM count 중간값
	FLEXPWM_0.SUB[0].VAL[1].R = 0x1046;             //0x0c80; // Modulo(Maximum) Count Value for the submodule counter // PWM count 최대값
	// FLEXPWM_0.SUB[0].VAL[2].R = 0x0000;      // Count value to set PWMA high
	// FLEXPWM_0.SUB[0].VAL[3].R = 0x0000;      // Count value to set PWMA low
	// FLEXPWM_0.SUB[0].VAL[4].R = 0x0000;      // Count value to set PWMB high
	// FLEXPWM_0.SUB[0].VAL[5].R = 0x0000;      // Count value to set PWMB low
	// FLEXPWM_0.SUB[0].OCTRL.B.PWMA_IN = 0;  // PWM A Input Logic Value
	// FLEXPWM_0.SUB[0].OCTRL.B.PWMB_IN = 0;  // PWM B Input Logic Value
	// FLEXPWM_0.SUB[0].OCTRL.B.PWMX_IN = 0;  // PWM X Input Logic Value
	
	// PWM 파형이 반대가 된다. 극성을 반전시키는 코드
	// FLEXPWM_0.SUB[0].OCTRL.B.POLA    = 0;  // PWM A Output Polarity : PWMA output not Inverted  // 반전시켜준다.
	// FLEXPWM_0.SUB[0].OCTRL.B.POLB    = 0;  // PWM B Output Polarity : PWMB output not Inverted  // 반전시켜준다.
	// FLEXPWM_0.SUB[0].OCTRL.B.POLX    = 0;  // PWM X Output Polarity : PWMX output not Inverted  // 반전시켜준다.
	// FLEXPWM_0.SUB[0].OCTRL.B.PWMAFS  = 0b00; // PWM A Fault State : Output is forced to logic 0
	// FLEXPWM_0.SUB[0].OCTRL.B.PWMBFS  = 0b00; // PWM B Fault State : Output is forced to logic 0
	// FLEXPWM_0.SUB[0].OCTRL.B.PWMXFS  = 0b00; // PWM X Fault State : Output is forced to logic 0

	FLEXPWM_0.SUB[0].TCTRL.R = 0x0004;   // Output Trigger Control Register

	// FLEXPWM_0.SUB[0].INTEN.R = 0x0000; //0x0003; // Interrupt Enable Register  1 : single sampling
	//        3 : double sampling
	// FLEXPWM_0.SUB[0].DMAEN.R = 0x0000;

	FLEXPWM_0.SUB[0].DISMAP.B.DISX = 0b1111; // PWM X Fault Mask : Turn off
	FLEXPWM_0.SUB[0].DISMAP.B.DISB = 0b0000; // PWM B Fault Mask : Turn on
	FLEXPWM_0.SUB[0].DISMAP.B.DISA = 0b0000; // PWM A Fault Mask : Turn on

	// Deadtime : 두개의 겹치는 파형이 둘다 ON이면 쇼트가 난다
	// 따라서 2개 파형 전부 OFF되는 타임을 주는것을 DEADTIME이라고 한다
	// FLEXPWM_0.SUB[0].DTCNT0.R = DTIME_CLOCK_PERIOD;  // PWM A Deadtime Count
	// FLEXPWM_0.SUB[0].DTCNT1.R = DTIME_CLOCK_PERIOD;  // PWM B Deadtime Count
	// FLEXPWM_0.SUB[0].DTCNT0.R = 0;  // PWM A Deadtime Count
	// FLEXPWM_0.SUB[0].DTCNT1.R = 0;  // PWM B Deadtime Count
	// FLEXPWM_0.SUB[0].CAPTCTRLX.R = 0x0000;
	// FLEXPWM_0.SUB[0].CAPTCOMPX.R = 0x0000;
}



