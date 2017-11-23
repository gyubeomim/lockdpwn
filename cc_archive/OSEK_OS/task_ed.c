/*
 * c++ ==> 시스템최신기술, OSEK_OS_EE를 사용해 torcs 프로그램과 CAN 통신으로 Driving Simulator를  PID 제어해보는 코드  
 */
#include "ee.h"
#include "Arduino.h"
#include "can.h"

double dt = 100;

short CC_trigger;
short LKAS_trigger;
float current_speed;

float target_speed;
float accel;
float brake;

float road_direction;
float yaw;

float toLeft;
float toRight;

float toMiddle;
float width;

float angle;
float lookahead;

float speed_error;
float lateral_error;

float left_steer ;
float right_steer ;
float steer_value;
float steer_lock = 0.366519; // Do not Edit.

// PID 제어 함수
double update(double curr_value, double P, double I, double D, int dt){
	double e =0 ;
	double e_int=0;
	double e_t;
	double int_e_max = 1;
	double int_e_min = 0;
	double de_t;
	double P_val;
	double I_val;
	double D_val;
	double PID_result;

	e_t =  curr_value;
	de_t = (e_t - e) / dt;

	e_int = e_int * e_t * dt;

	if (e_int  > int_e_max)
		e_int = int_e_max;
	else if (e_int  < int_e_min)
		e_int = int_e_min;

	P_val = P * e_t;
	I_val = I * e_int;
	D_val = D * de_t;

	PID_result = P_val + I_val + D_val;
	e = e_t;

	return PID_result;
}

ISR (isr){
	static int count = 1;
	if (count == 4){
		IncrementCounter(SysTimerCnt);
		count = 0;
	}
	count++;
}

TASK(RCV){

	unsigned char buf[8]={0};
	unsigned long id;
	unsigned char len;

	while(1){
		CAN_read(&id, &len, buf);
		if(len != 0){
			switch(id)	{
				case 0x0A0:
					memcpy(&CC_trigger, buf, sizeof(short));
					memcpy(&LKAS_trigger, buf+2, sizeof(short));
					memcpy(&current_speed, buf+4, sizeof(float));
					break;

				case 0x0A1:
					memcpy(&target_speed, buf, sizeof(float));
					// accel : 0 ~ 1 사이의 값 
					memcpy(&accel, buf+4, sizeof(float));
					break;

				case 0x0B0:
					// road_direction : 이미 설정된 디렉션 값
					memcpy(&road_direction, buf, sizeof(float));
					memcpy(&yaw, buf+4, sizeof(float));
					break;

				case 0x0B1:
					// toLeft : 보통 5정도의 값을 유지하는게 좋다
					memcpy(&toLeft, buf, sizeof(float));
					memcpy(&toRight, buf+4, sizeof(float));
					break;

				case 0x0B2:
					memcpy(&toMiddle, buf, sizeof(float));
					memcpy(&width, buf+4, sizeof(float));
					break;
				case 0x0C0:
					// speed_error : 사용하지 않는게 좋다. 계산이 정확히 안되서 나온다
					// lateral_error : toLeft의 개념과 비슷.
					memcpy(&speed_error, buf, sizeof(float));
					memcpy(&lateral_error, buf+4, sizeof(float));
					break;
				default:
					break;
			}
		}
		else
			break;
	}
	TerminateTask();
};


TASK(CC) {
	unsigned char buf[8];

	target_speed = 150;
	double P = 100;
	double I = 55;
	double D = 35;
	double u = 0;
	double error_acc = 0;

	// s : 크루즈를 키는 버튼
	// x : LKAS를 키는 버튼
		
	// 크루즈를 켰다는 의미 	
	if(CC_trigger > 0.5){
		/* Implementation */
		error_acc = (target_speed - current_speed) * 0.01;
		u = update(error_acc, P, I, D, dt);

		if(u > target_speed) u = target_speed;
		else if(u < 0) {
			u = 0;
			//brake = 0.1;
		}
		accel = u / target_speed;
	}
	else
		accel = 0;


	// accel ==> buf 에 값 전달
	memcpy(buf, &accel, sizeof(float));
	memcpy(buf+4, &brake, sizeof(float));

	CAN_write(0x0A5, 8, buf);
	TerminateTask();
};

TASK(LKAS){

	unsigned char buf[8];
	float angle;

	double P2 = 2;
	double I2 = 1;
	double D2 = 1;

	double v = 0;
	double error_dist = 0;

	if(LKAS_trigger > 0.5){
		// error는 road_direction - yaw 값으로 한다
		error_dist = road_direction - yaw;
		v = update(error_dist, P2,I2,D2, dt);
		angle = v;

		/* Don't Edit This Function */
		Calculate_Steer_Value(angle);
        /****************************/
	}
	else{
		left_steer = right_steer = 0.0;
	}

	memcpy(buf, &left_steer, sizeof(float));
	memcpy(buf+4, &right_steer, sizeof(float));

	CAN_write(0x0B5, 8, buf);

	TerminateTask();
};

   /* Do NOT Edit This Function */
void Calculate_Steer_Value(float angle){
	steer_value = angle/steer_lock;

	if(steer_value>0.0){
		if(steer_value > 1.0){
			steer_value = 1.0;
		}
		left_steer = steer_value;
		right_steer = 0.0;
	}

	else if(steer_value < 0.0){
		if(steer_value < -1.0){
			steer_value = -1.0;
		}
		right_steer = -(steer_value);
		left_steer = 0.0;
	}

}



