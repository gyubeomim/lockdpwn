/*
 *	freescale c ==> RC Car Line Follower Code Using PID (without Encoder)(not Perfectly Used)
 *					20101447 임규범
 *				 	20101463 허성문
 *				 	16/12/05(월)
 *	
 *	RC Car 제품명 : TT-02B SHAFT DRIVEN 4WD CHASSIS, NEO SCORCHER (+ Servo Motor, DC Motor, DC Motor 수신기 포함)
 *	MCU 제품명 : Freescale MPC5604P
 *
 *  ps0 : 조향각이 없이 단순히 DC Motor 2개로 작동하는 라인트레이서가 아니라 RC Car를 개조해서 만든 라인트레이서의 코드로 Servo Motor, DC Motor의 속도를 조정해 짧은 시간에 반응성을 최대한 끌어올려야 하므로 조금 더 복잡한 조건문과 변수들을 많이 사용했습니다.
 *	ps1 : DC Motor, Servo Motor 모두 PID 제어를 사용했으나 실제로 엔코더를 통한 Feedback이 아니므로 완벽한 의미의 PID 제어는 아닙니다. 
 *	ps2 : RC Car 라인트레이서에서 PID를 사용한 이유는 DC Motor와 Servo Motor의 부드러운 움직임을 얻기 위해서 입니다.
 *
 *	final ps + 대회 성적은 망했습니다. 이 코드는 참고용으로만 사용해주세요
 *			 + 구동축 앞바퀴는 무조건 빼고 드리프트를 사용하면서 브레이크를 하면 서보모터로도 급한 각도도 고속으로 꺽을 수 있습니다
 *			 + 아래 코드는 구동축 앞바퀴를 뺀 코드가 아닙니다
 */
#include "MPC5604P_M26V.h"
#include "freemaster.h"
#include "init_base.h"

// Servo Motor 각도 선언문
// 1550이 정중앙값이고
// +-450의 값에 따라 왼쪽 끝, 오른쪽 끝으로 움직인다
#define SERVOMIDDLE 1550
#define SERVORANGE 900
#define PIDMIN -SERVORANGE/2
#define PIDMAX SERVORANGE/2

// DC Motor 속도 관련 선언문
// 705가 라인트레이서의 최고속도이고 745(+40)이 모터의 최저속도이다
// 해당 RC Car는 DC Motor 속도를 조절하는 방식이 약간 특이하다
#define LIMITEDMOTORMAXSPEED 705
#define PIDMAXDCMotor LIMITEDMOTORMAXSPEED+40

// PIT 타이머 3개의 주기 관련 선언문
#define INTERRUPTINTERVAL 640000  // 0.01초 
#define INTERRUPTINTERVAL2 32000000  // 0.5초
#define INTERRUPTINTERVAL3 64000000  // 1초

// 적외선센서의 갯수 : 4개
#define NUM_SENSORS 4

// 가독성을 높이기 위해 TRUE 1 , FALSE 0을 사용했습니다
#define TRUE 1
#define FALSE 0

// 각종 변수들을 초기화합니다
double servoControl = SERVOMIDDLE;
double motorControl = LIMITEDMOTORMAXSPEED;

int SensorErrorAmount = 0;
double DisturbanceAmount = 0;

int BrakeTimer = 0;
int BrakeTimer2 = 0;
int SuperBrakeTime = 0;
int IsInOutLine = 0;
int ShakingTime = 0;
int Brakeflag1 = 1;
int Brakeflag2 = 1;
int ADCspeedController = 0;

int lastTracesensorValue = 0;
int sensorValues[NUM_SENSORS];

// PID codes for Servo Motor
double Kp = 10;
double Ki = 5;
double Kd = 5;
double setPointServo = 0;  // SetPoint : 서보모터가 정중앙일 때 Error = 0 으로 설정한다
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

// PID codes for DC Motor
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

// 적외선 센서를 편리하게 사용하기 위한 구조체 선언
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

// SENSOR의 구조체 이름을 tracesensor로 선언합니다
struct SENSOR tracesensor;

// 적외선 센서값을 읽어서 tracesensor 구조체 안에 저장하는 함수
// sensorValues[] 배열 안에도 넣어서 Servo Motor의 PID 제어에 활용합니다
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

	// lastTracesensorValue 값에 바로 이전에 센서값을 넣어서 SensorErrorAmount와 DisturbanceAmount를 제어하는데 사용합니다
	// 위 두 값은 PIT 타이머에 의해 특정시간마다 0으로 초기화되는데
	// 너무 빨리 센서의 값이 바뀌면(차량의 진동이 심하면) DC Motor의 속도를 줄이기 위해서 삽입한 코드입니다.
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
	int i = 0;

	// 11은 아무 의미없는 값입니다 (posLeft,Right의 값이 바뀌는지 검사하기 위해 넣은 값)
	int posLeft = 11;
	int posRight = 11;


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

// Servo Motor PID 제어 함수입니다.
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

	// 센서값이 중간값인 경우 조향을 full로 꺽을 필요 없으므로 다음 조건문을 추가해서
	// 끝까지 조향이 꺽이지 않게 제어합니다
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

// DC Motor PID 제어 함수입니다.
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

// PIT 타이머 초기화 함수
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

// 가변저항(Analog)을 전기적 Digital 신호로 사용하기 위해 초기화 선언을 해주는 함수
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

// DC Motor의 속도를 제어하기 위해 가변저항을 사용합니다
void MotorSpeedADCRead()
{
	ADC_1.MCR.B.NSTART = 1;  // Module 1 Conversion Start
	asm("nop");  
	
	while(ADC_1.MCR.B.NSTART)
	{
		asm("nop");
	}

	ADCspeedController = ADC_1.CDR[5].B.CDATA;

	// DC Motor는 700(최고속도) 750(최저속도)의 값을 가지므로 속도의 제한을 걸어줍니다 
	if(ADCspeedController <= LIMITEDMOTORMAXSPEED)
	{
		ADCspeedController = LIMITEDMOTORMAXSPEED;
	}
}

// Motor들을 사용하기 위한 PWM 초기화 함수
void init_FlexPWM0(void) 
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

// SERVO MOTOR 제어를 위해 0번 모튤 초기화하는 함수
// PWM 신호폭을 +-2500(총 5000)의 범위로 하고 Clock은 200Hz로 설정합니다 
void init_FlexPWM0_Servo(void) 
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

// DC MOTOR 제어를 위해 1번 모듈 초기화하는 함수
// PWM 신호폭을 +-2500(총 5000)의 범위로 하고 Clock은 200Hz로 설정합니다 
void init_FlexPWM0_DCMotor(void) 
{
//-----------------------------------------------------------------------
//     FlexPWM Submodule0 Configuration Initialization code for FLEXPWM_1 Device
//-----------------------------------------------------------------------
    /*PWM SUB[1] setting 200Hz servo*/
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

// 라인트레이싱을 하면서 센서값에 따라 DC Motor의 속도를 제어하는 함수
// 타이머와 조건문을 사용해 진동이 심할 경우 감속하도록 설정했습니다.
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
			
			// 특정시간동안 0b1111만 읽힌경우 밖에있는걸로 간주하고 
			// 다시 선 안으로 복귀할 때 속도가 너무 빠르면 안되므로 모터의 감속하는 조건문
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

	// 차량의 진동이 너무 심해서 제대로 라인을 따라가지 못할 경우
	// DisturbanceAmount 값이 증가하게 되고 이 값이 증가한만큼
	// DC Motor의 속도를 감소시킵니다
	if(DisturbanceAmount >= 10 && DisturbanceAmount <= 50 && tracesensor.sen.R != 0b0111 && tracesensor.sen.R != 0b1110)
	{
		motorControl += DisturbanceAmount/3;
	}

	// 모터의 속도가 너무 느리면 정지하므로 상한값을 설정합니다
	if(motorControl >= PIDMAXDCMotor)
	{
		motorControl = PIDMAXDCMotor;
	}
	
	// PID 제어로 Error 값을 얻기 위해 motorControl의 값을 사용합니다
	inputDCMotor = motorControl;
}

// 최종적으로 PID 제어를 통해 계산된 servoControl, motorControl 값이 PWM 신호로 인가되기 위한 함수
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

// 타이머1 : 일정시간마다 실행되는 함수로 각종 다른 Timer들을 실행시키면서 PID 계산을 수행하는 함수
void TimerforPIDCompute()
{
	BrakeTimer++;
	BrakeTimer2++;
	IsInOutLine++;

	// 일정시간마다 SuperBrakeTime 값을 0으로 초기화시키는 함수
	// SuperBrakeTime : 차량의 진동이 심한 경우 DC Motor의 속도를 낮추기 위해 사용하는 변수
	if(BrakeTimer >= 30)  
	{
		BrakeTimer = 0;
		SuperBrakeTime = 0;
	}

	// 일정시간마다 ShakingTime 값을 0으로 초기화시키는 함수
	// ShakingTime : SuperBrakeTime 값에 의해 1차적으로 속도가 늦춰지고 그래도 진동이 심하면 일정시간 더 모터의 속도를 늦추기 위한 변수
	if(BrakeTimer2 >= 100)
	{
		BrakeTimer2 = 0;
		ShakingTime = 0;
	}

	// DC Motor, Servo Motor의 PID 제어 코드
	PIDComputeforServo(&setPointServo, &input, &servoControl, Kp, Ki, Kd, PIDMIN, PIDMAX,IsMiddle);
	PIDComputeforDCMotor(&setPointDCMotor, &inputDCMotor, &motorControl, Kp2, Ki2, Kd2, LIMITEDMOTORMAXSPEED, PIDMAXDCMotor);

	PIT.CH[0].TFLG.B.TIF = 1;  // Clear PIT0 flag
}

// 타이머2 : 일정시간마다 수행되며 라인트레이서의 진동을 감지하기 위해 사용하는 함수
void TimerforRecognizeShake()
{
	SensorErrorAmount = 0;
	DisturbanceAmount = 0;
	PIT.CH[1].TFLG.B.TIF = 1;  // Clear PIT1 flag
}

// 타이머3 : 차량이 선밖으로 빠져나간 다음 다시 선 안으로 복귀할 때 속도가 너무 빠르므로
// 			 IsInOutLine 값에 따라 선 안으로 복귀하기 전에 DC Motor의 속도를 감소시키는 함수
void OneSecondTimer()
{
	IsInOutLine++;
	PIT.CH[2].TFLG.B.TIF = 1;  // Clear PIT2 flag
}

int main(void)
{
	// Freescale의 기본 초기화 코드 
	initModesAndClock();
	disableWatchdog();
	enableIrq();
	FMSTR_Init();
	init_INTC();	   		
	init_Linflex0();
	INTC.CPR.B.PRI = 0;

	// PWM과 ADC, PIT의 초기화 코드
	init_FlexPWM0();
	init_FlexPWM0_Servo();
	init_FlexPWM0_DCMotor();
	init_MotorSpeedADC();
	init_PITforPID();

	// 일정시간마다 실행되는 3개의 Timer 코드
	INTC_InstallINTCInterruptHandler(TimerforPIDCompute,59,6);
	INTC_InstallINTCInterruptHandler(TimerforRecognizeShake,60,7);
	INTC_InstallINTCInterruptHandler(OneSecondTimer,61,8);

	// 적외선센서 4개 초기화 코드
	SIU.PCR[44].R = 0x0100;  // Sensor1 C[12] PWM1A
	SIU.PCR[45].R = 0x0100;  // Sensor1 C[13] PWM1B
	SIU.PCR[46].R = 0x0100;  // Sensor1 C[14] PWM2A
	SIU.PCR[47].R = 0x0100;  // Sensor1 C[15] PWM2B

	// DC Motor, Servo Motor의 PWM 신호를 주기위해 초기화하는 코드
	SIU.PCR[58].R = 0x0600; // PD10 : PWM A[0] SERVO
	SIU.PCR[61].R = 0x0600; // PD13 : PWM A[1] DC

	// 가변저항값을 통해 DC Motor의 속도를 제어하기 위해 사용하는 초기화코드
	SIU.PCR[64].R = 0x2400;  // ADC 사용을 위해 E0 포트 설정 

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

