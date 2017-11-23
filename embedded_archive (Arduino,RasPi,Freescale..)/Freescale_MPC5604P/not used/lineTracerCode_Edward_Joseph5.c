/*
 *	freescale c ==> 라인트레이서 코드
 *					20101447 임규범
 *				 	20101463 허성문
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_base.h"

#define SERVOMIDDLE 1550
#define SERVORANGE 900
#define PIDMIN -SERVORANGE/2
#define PIDMAX SERVORANGE/2

#define LIMITEDMOTORMAXSPEED 705
#define PIDMAXDCMotor LIMITEDMOTORMAXSPEED+40

#define INTERRUPTINTERVAL 640000  // 0.01초 
#define INTERRUPTINTERVAL2 32000000  // 0.5초
#define INTERRUPTINTERVAL3 64000000  // 1초
#define NUM_SENSORS 4

#define TRUE 1
#define FALSE 0

double servoControl = SERVOMIDDLE;
double motorControl = LIMITEDMOTORMAXSPEED;
double DisturbanceAmount = 0;
int BrakeTimer = 0;
int BrakeTimer2 = 0;
int SuperBrakeTime = 0;
int IsInOutLine = 0;
int ShakingTime = 0;
int SensorErrorAmount = 0;
int Brakeflag1 = 1;
int Brakeflag2 = 1;
int ADCspeedController = 0;
int lastTracesensorValue = 0;
int sensorValues[NUM_SENSORS];

// PID codes for Servo
double Kp = 10;
double Ki = 5;
double Kd = 5;
double setPointServo = 0;  // SetPoint는 정중앙을 달리고 있어서 Error = 0 임을 의미한다
double input = 0;
double *mySetpoint;
double *myInput;
double outMax;
double outMin;
double error;
double ITerm;
double dInput;
double output;
double lastInput;
int IsMiddle;

// PID codes for DCMotor
double Kp2 = .2;
double Ki2 = .1;
double Kd2 = .1;
double setPointDCMotor = 0;  
double input2 = 0;
double inputDCMotor = 0;
double *mySetpoint2;
double *myInput2;
double outMax2;
double outMin2;
double error2;
double ITerm2;
double dInput2;
double output2;
double lastInput2;

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

void Sensing()
{
	tracesensor.sen.B.sensor1 = SIU.GPDI[44].B.PDI;
	tracesensor.sen.B.sensor2 = SIU.GPDI[45].B.PDI;
	tracesensor.sen.B.sensor3 = SIU.GPDI[46].B.PDI;
	tracesensor.sen.B.sensor4 = SIU.GPDI[47].B.PDI;


	if(tracesensor.sen.B.sensor1)
	{
		sensorValues[0] = 1;
	}
	else
	{
		sensorValues[0] = 0;
	}

	if(tracesensor.sen.B.sensor2)
	{
		sensorValues[1] = 1;
	}
	else
	{
		sensorValues[1] = 0;
	}

	if(tracesensor.sen.B.sensor3)
	{
		sensorValues[2] = 1;
	}
	else
	{
		sensorValues[2] = 0;
	}

	if(tracesensor.sen.B.sensor4)
	{
		sensorValues[3] = 1;
	}
	else
	{
		sensorValues[3] = 0;
	}



	if(lastTracesensorValue != tracesensor.sen.R)
	{
		SensorErrorAmount++;

		if(SensorErrorAmount <= 30)
		{
			DisturbanceAmount++;
		}
	}
	lastTracesensorValue = tracesensor.sen.R;
}

// Servo 모터 PID 계산을 위해 Input값을 계산하는 함수
void CalculateInputFromSensor()
{
	int sum = 0;
	int posLeft = 11;
	int posRight = 11;
	int i = 0;
	for (i=0; i < NUM_SENSORS/2; i++)   // 오른쪽 2개 센서값
	{
		if(sensorValues[i] == 0)
		{
			sum += 1;
			posRight = i - 1;
		}
	}
	for (i = NUM_SENSORS-1; i >= NUM_SENSORS/2; i--) // 왼쪽 2개 센서값
	{
		if(sensorValues[i] == 0)
		{
			sum += 1;
			posLeft = i - 2;
		}
	}

	sum = sum*10;

	if((posLeft != 11) && (posRight != 11)) // 0b1001, 0b0000의 경우
	{
		input = 0;
	}
	else if(posLeft != 11)   // 0b1110, 0b1100, 0b1101 의 경우
	{
		input = posLeft*20 + sum;  // 0b1110 : (3-2)*20 + 1*10 = 30
								   // 0b1100 : (2-2)*20 + 2*10 = 20
								   // 0b1101 : (2-2)*20 + 1*10 = 10
	}
	else if(posRight != 11)  // 0b0111, 0b0011, 0b1011 의 경우
	{
		input = posRight*20 - sum; // 0b0111 : (0-1)*20 -10 = -30
		  						   // 0b0011 : (1-1)*20 -20 = -20
		 						   // 0b1011 : (1-1)*20 - 10 = -10
	}
}

void PIDComputeforServo(double *setpointPID, double *inputPID, double *outputPID, double kp, double ki, double kd, double Min, double Max, int IsMiddle)
{
	outMin = Min;
    outMax = Max;

    myInput = inputPID;
    mySetpoint = setpointPID;

	/*Compute all the working error variables*/
	input = *myInput;
	error = *mySetpoint - input;

	ITerm += (ki * error);
	if(ITerm > outMax) ITerm= outMax;
	else if(ITerm < outMin) ITerm= outMin;
	dInput = (input - lastInput);

	/*Compute PID Output*/
	output = kp*error + ITerm - kd*dInput;

	if(output > outMax) output = outMax;
	else if(output < outMin) output = outMin;

	// 센서값이 중간값인 경우 조향을 full로 꺽을 필요 없으므로
	if(IsMiddle)
	{
		if(output > 0)
		{
			output -= 300;
		}
		else
		{
			output += 300;
		}
	}

	*outputPID = output + SERVOMIDDLE;

	/*Remember some variables for next time*/
	lastInput = input;
}

void PIDComputeforDCMotor(double *setpointPID, double *inputPID, double *outputPID, double kp, double ki, double kd, double Min, double Max)
{
	outMin2 = Min;
    outMax2 = Max;

    myInput2 = inputPID;
    mySetpoint2 = setpointPID;

	/*Compute all the working error variables*/
	input2 = *myInput2;
	error2 = *mySetpoint2 - input2;

	ITerm2 += (ki * error2);
	if(ITerm2 > outMax2) ITerm2= outMax2;
	else if(ITerm2 < outMin2) ITerm2= outMin2;
	dInput2 = (input2 - lastInput2);

	/*Compute PID Output*/
	output2 = kp*error2 + ITerm2 - kd*dInput2;

	if(output2 > outMax2) output2 = outMax2;
	else if(output2 < outMin2) output2 = outMin2;

	*outputPID = output2;

	/*Remember some variables for next time*/
	lastInput2 = input2;
}

// PIT 초기화 코드
void init_PITforPID()
{
	PIT.PITMCR.R = 0x00000001;  // Enable PIT and Config Stop in debug mode.

	// PIT channel 0 초기화 (초마다 생성)
	PIT.CH[0].LDVAL.R = INTERRUPTINTERVAL; // 64000000 // Timeout = (64M * 1 sec / 64M sysclocks = 1s)
	PIT.CH[0].TCTRL.R = 0x3;  // Enable PIT0 interrupt & start PIT counting

	// PIT channel 1 초기화 (0.5초마다 생성
	PIT.CH[1].LDVAL.R = INTERRUPTINTERVAL2; // 32000000 // Timeout = (32M * 1 sec / 64M sysclocks = 0.5s)
	PIT.CH[1].TCTRL.R = 0x3;  // Enable PIT0 interrupt & start PIT counting

	PIT.CH[2].LDVAL.R = INTERRUPTINTERVAL3;
	PIT.CH[2].TCTRL.R = 0x3;  // Enable PIT0 interrupt & start PIT counting
}

void init_MotorSpeedADC()
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

void MotorSpeedADCRead()
{
	ADC_1.MCR.B.NSTART = 1;  // Module 1 Conversion Start
	asm("nop");  
	
	while(ADC_1.MCR.B.NSTART)
	{
		asm("nop");
	}

	ADCspeedController = ADC_1.CDR[5].B.CDATA;

	if(ADCspeedController <= LIMITEDMOTORMAXSPEED)
	{
		ADCspeedController = LIMITEDMOTORMAXSPEED;
	}
}

void init_FlexPWM0(void) // 모터 초기화 코드
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

void init_FlexPWM0_Servo(void) // SERVO MOTOR 제어를 위해 0번 모튤 초기화
{
//-----------------------------------------------------------------------
//     FlexPWM Submodule0 Configuration Initialization code for FLEXPWM_0 Device
//-----------------------------------------------------------------------
    /*PWM SUB[0] setting 200Hz servo*/
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

void init_FlexPWM0_DCMotor(void) // DC MOTOR 제어를 위해 1번 모듈 초기화
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

void LineTracing()
{
	switch(tracesensor.sen.R)
	{
		case 0b1111:
			if(ShakingTime)
			{
				setPointDCMotor = ADCspeedController + 19;
			}
			else
			{
				setPointDCMotor = ADCspeedController + 5;
			}
			
			// 특정시간동안 0b1111만 읽힌경우 밖에있는걸로 간주하고 감속한다
			if(IsInOutLine >= 50)
			{
				setPointDCMotor = ADCspeedController + 13;
			}
			IsMiddle = FALSE;
			break;
		case 0b0000:    							// 모두 검정색일 때
			setPointDCMotor = ADCspeedController + 50;
			IsMiddle = FALSE;
			break;
		case 0b1001:
			servoControl = SERVOMIDDLE;
			if(ShakingTime)
			{
				setPointDCMotor = ADCspeedController + 31;
			}
			else
			{
				setPointDCMotor = ADCspeedController;
			}
			IsInOutLine = FALSE;
			break;
		case 0b1011:
			if(ShakingTime)
			{
				setPointDCMotor = ADCspeedController + 31;
			}
			else
			{
				setPointDCMotor = ADCspeedController + 1;
			}
			IsInOutLine = FALSE;
			IsMiddle = TRUE;
			break;
		case 0b1101:
			if(ShakingTime)
			{
				setPointDCMotor = ADCspeedController + 31;
			}
			else
			{
				setPointDCMotor = ADCspeedController + 1;
			}
			IsInOutLine = FALSE;
			IsMiddle = TRUE;
			break;
		case 0b0011:
			if(SuperBrakeTime && Brakeflag1)
			{
				Brakeflag1 = FALSE;
				Brakeflag2 = TRUE;
				ShakingTime = TRUE;
			}
			SuperBrakeTime = TRUE;

			if(ShakingTime)
			{
				setPointDCMotor = ADCspeedController + 31;
			}
			else
			{
				setPointDCMotor = ADCspeedController + 1;
			}
			IsInOutLine = FALSE;
			IsMiddle = TRUE;
			break;
		case 0b1100:
			if(SuperBrakeTime && Brakeflag2)
			{
				Brakeflag1 = TRUE;
				Brakeflag2 = FALSE;
				ShakingTime = TRUE;
			}
			SuperBrakeTime = TRUE;

			if(ShakingTime)
			{
				setPointDCMotor = ADCspeedController + 31;
			}
			else
			{
				setPointDCMotor = ADCspeedController + 1;
			}
			IsInOutLine = FALSE;
			IsMiddle = TRUE;
			break;
		case 0b1110: 							
			if(SuperBrakeTime && Brakeflag2)
			{
				Brakeflag1 = TRUE;
				Brakeflag2 = FALSE;
				ShakingTime = TRUE;
			}
			SuperBrakeTime = TRUE;
			IsInOutLine = FALSE;
			IsMiddle = FALSE;

			if(ShakingTime)
			{
				setPointDCMotor = ADCspeedController + 13;
			}
			else
			{
				setPointDCMotor = ADCspeedController + 10;
			}
			break;
		case 0b0111: 						
			if(SuperBrakeTime && Brakeflag1)
			{
				Brakeflag1 = FALSE;
				Brakeflag2 = TRUE;
				ShakingTime = TRUE;
			}
			SuperBrakeTime = TRUE;
			IsInOutLine = FALSE;
			IsMiddle = FALSE;

			if(ShakingTime)
			{
				setPointDCMotor = ADCspeedController + 13;
			}
			else
			{
				setPointDCMotor = ADCspeedController + 10;
			}
			break;
		default:
			setPointDCMotor = ADCspeedController + 20;
			IsInOutLine = FALSE;
			IsMiddle = FALSE;
			break;
	}

	if(DisturbanceAmount >= 10 && DisturbanceAmount <= 50 && tracesensor.sen.R != 0b0111 && tracesensor.sen.R != 0b1110)
	{
		motorControl += DisturbanceAmount/3;
	}

	if(motorControl >= PIDMAXDCMotor)
	{
		motorControl = PIDMAXDCMotor;
	}
	inputDCMotor = motorControl;
}

void DCServoMotorControlPWM()
{
	if(servoControl >= SERVOMIDDLE + PIDMIN && servoControl <= SERVOMIDDLE + PIDMAX)
	{
		FLEXPWM_0.SUB[0].VAL[2].R = (unsigned short) -servoControl;
		FLEXPWM_0.SUB[0].VAL[3].R = (unsigned short)  servoControl;
	}

	FLEXPWM_0.SUB[1].VAL[2].R = (unsigned short)(int) -motorControl;
	FLEXPWM_0.SUB[1].VAL[3].R = (unsigned short)(int) motorControl;

	FLEXPWM_0.MCTRL.B.LDOK |= 0xf;
	FLEXPWM_0.MCTRL.B.RUN |= 0xf;
}

void TimerforPIDCompute()
{
	BrakeTimer++;
	BrakeTimer2++;
	IsInOutLine++;
	if(BrakeTimer >= 30)  
	{
		BrakeTimer = 0;
		SuperBrakeTime = 0;
	}
	if(BrakeTimer2 >= 100)
	{
		BrakeTimer2 = 0;
		ShakingTime = 0;
	}


	PIDComputeforServo(&setPointServo, &input, &servoControl, Kp, Ki, Kd, PIDMIN, PIDMAX,IsMiddle);
	PIDComputeforDCMotor(&setPointDCMotor, &inputDCMotor, &motorControl, Kp2, Ki2, Kd2, LIMITEDMOTORMAXSPEED, PIDMAXDCMotor);
	PIT.CH[0].TFLG.B.TIF = 1;  // Clear PIT0 flag
}

void TimerforRecognizeShake()
{
	SensorErrorAmount = 0;
	DisturbanceAmount = 0;
	PIT.CH[1].TFLG.B.TIF = 1;  // Clear PIT1 flag
}

void OneSecondTimer()
{
	IsInOutLine++;
	PIT.CH[2].TFLG.B.TIF = 1;  // Clear PIT2 flag
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

	init_FlexPWM0();
	init_FlexPWM0_Servo();
	init_FlexPWM0_DCMotor();
	init_MotorSpeedADC();
	init_PITforPID();

	INTC_InstallINTCInterruptHandler(TimerforPIDCompute,59,6);
	INTC_InstallINTCInterruptHandler(TimerforRecognizeShake,60,7);
	INTC_InstallINTCInterruptHandler(OneSecondTimer,61,8);

	// 적외선센서 4개 초기화 코드
	SIU.PCR[44].R = 0x0100;  // Sensor1 C[12] PWM1A
	SIU.PCR[45].R = 0x0100;  // Sensor1 C[13] PWM1B
	SIU.PCR[46].R = 0x0100;  // Sensor1 C[14] PWM2A
	SIU.PCR[47].R = 0x0100;  // Sensor1 C[15] PWM2B

	SIU.PCR[58].R = 0x0600; // PD10 : PWM A[0] SERVO
	SIU.PCR[61].R = 0x0600; // PD13 : PWM A[1] DC

	SIU.PCR[64].R = 0x2400;  // E0 포트 설정 (ADC_1 가변저항 파란색 움직이는거 사용한다고 선언)

	/* Loop forever */
	while(1)
	{
		FMSTR_Recorder();
		FMSTR_Poll();

		MotorSpeedADCRead();
		Sensing();
		LineTracing();
		CalculateInputFromSensor();
		DCServoMotorControlPWM();
	}
}

