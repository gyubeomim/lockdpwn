#ifndef DCMOTOR_MNG_H
#define DCMOTOR_MNG_H

#include <Arduino.h>



//모터1 제어핀
#define MOTOR_PIN1 7
#define MOTOR_PIN2 8

//모터2 제어핀
#define MOTOR_PIN3 9
#define MOTOR_PIN4 10

//모터1 pwm핀
#define MOTOR_PWM1 5

//모터2 pwm핀
#define MOTOR_PWM2 6


class CDCMotorDriver
{
protected:
	char m_cPin1;	//모터1제어핀, IN1, IN2, 모터1은 좌측 모터라 하겠습니다.
	char m_cPin2;

	char m_cPin3;	//모터2 제어핀, IN3, IN4, 모터2는 우측 모터라 하겠습니다.
	char m_cPin4;

	char m_cPwm1;	//모터1 PWM 제어핀, ENA
	char m_cPwm2;	//모터2 PWM 제어핀, ENB

	bool m_bEnablePWM;

public:
	/*
	pwm제어를 사용하지 않는경우, pwm1, pwm2에는 0을 bEnablePWM에는 false를
	*/
	CDCMotorDriver(int pin1, int pin2, int pin3, int pin4, int pwm1, int pwm2, bool bEnablePWM)
	{
		m_cPin1 = (char)pin1;
		m_cPin2 = (char)pin2;
		m_cPin3 = (char)pin3;
		m_cPin4 = (char)pin4;

		m_cPwm1 = (char)pwm1;
		m_cPwm2 = (char)pwm2;

		m_bEnablePWM = bEnablePWM;
	}

	void Init()
	{
		pinMode(m_cPin1, OUTPUT);
		pinMode(m_cPin2, OUTPUT);
		pinMode(m_cPin3, OUTPUT);
		pinMode(m_cPin4, OUTPUT);
		pinMode(m_cPwm1, OUTPUT);
		pinMode(m_cPwm2, OUTPUT);

		StopAll();
	}

	//두 모터를 정회전 제어한다. 
	//leftspeed : 0 ~ 255사이의 값으로 모터 속도를 제어, pwm제어를 하지 않을경우 0
	//rightspeed : 0 ~ 255사이의 값으로 모터 속도를 제어, pwm제어를 하지 않을경우 0
	void ForwardAll(unsigned char leftspeed, unsigned char rightspeed)
	{
		Forward(true, leftspeed);
		Forward(false, rightspeed);
	}

	//두 모터를 같은 속도로 역회전 제어한다. 
	//leftspeed : 0 ~ 255사이의 값으로 모터 속도를 제어, pwm제어를 하지 않을경우 0
	//rightspeed : 0 ~ 255사이의 값으로 모터 속도를 제어, pwm제어를 하지 않을경우 0
	void BackwardAll(unsigned char leftspeed, unsigned char rightspeed)
	{
		Backward(true, leftspeed);
		Backward(false, rightspeed);
	}

	//모든 모터를 정지 시킨다
	void StopAll()
	{
		Stop(true);
		Stop(false);
	}

	//좌측 모터를 해당 속도로 정회전
	//speed : 모터 제어속도, 0 ~ 255, pwm제어를 하지 않을경우 0
	void ForwardLeftMotor(unsigned char speed)
	{
		Forward(true, speed);
	}
	
	//우측 모터를 해당 속도로 정회전
	//speed : 모터 제어속도, 0 ~ 255, pwm제어를 하지 않을경우 0
	void ForwardRightMotor(unsigned char speed)
	{
		Forward(false, speed);
	}

	//좌측 모터를 해당 속도로 역회전
	//speed : 모터 제어속도, 0 ~ 255, pwm제어를 하지 않을경우 0
	void BackwardLeftMotor(unsigned char speed)
	{
		Backward(true, speed);
	}

	//우측 모터를 해당 속도로 역회전
	//speed : 모터 제어속도, 0 ~ 255, pwm제어를 하지 않을경우 0
	void BackwardRightMotor(unsigned char speed)
	{
		Backward(false, speed);
	}

	//좌측 모터만 정지
	void StopLeft()
	{
		Stop(true);
	}

	//우측 모터만 정지
	void StopRight()
	{
		Stop(false);
	}

	// 좌측 또는 우측 모터를 해당 속도로 정회전 제어한다
	// bMotor1 이 true일경우 좌측 모터 false 이면 우측모터
	// speed : 모터 제어속도, 0 ~ 255, pwm 제어를 하지 않을경우 0
	void Forward(bool bMotor1, unsigned char speed)
	{
		if (bMotor1)
		{
			digitalWrite(m_cPin1, HIGH);
			digitalWrite(m_cPin2, LOW);

			if (m_bEnablePWM)
			{
				if (speed >= 255)
					digitalWrite(m_cPwm1, HIGH);
				else
					analogWrite(m_cPwm1, speed);
			}
		}
		else
		{
			digitalWrite(m_cPin3, HIGH);
			digitalWrite(m_cPin4, LOW);

			if (m_bEnablePWM)
			{
				if (speed >= 255)
					digitalWrite(m_cPwm2, HIGH);
				else
					analogWrite(m_cPwm2, speed);
			}
		}
	}

	//좌측 또는 우측 모터를 해당 속도로 역회전 제어한다
	//bMotor1 이 true일경우 좌측 모터 false 이면 우측모터
	//speed : 모터 제어속도, 0 ~ 255, pwm제어를 하지 않을경우 0
	void Backward(bool bMotor1, unsigned char speed)
	{
		if (bMotor1)
		{
			digitalWrite(m_cPin1, LOW);
			digitalWrite(m_cPin2, HIGH);

			if (m_bEnablePWM)
			{
				if (speed >= 255)
					digitalWrite(m_cPwm1, HIGH);
				else
					analogWrite(m_cPwm1, speed);
			}
		}
		else
		{
			digitalWrite(m_cPin3, LOW);
			digitalWrite(m_cPin4, HIGH);

			if (m_bEnablePWM)
			{
				if (speed >= 255)
					digitalWrite(m_cPwm2, HIGH);
				else
					analogWrite(m_cPwm2, speed);
			}
		}
	}

	//좌측 또는 우측 모터를 정지 시킨다
	//bMotor1 이 true일경우 좌측 모터 false 이면 우측모터
	void Stop(bool bMotor1)
	{
		if (bMotor1)
		{
			digitalWrite(m_cPin1, LOW);
			digitalWrite(m_cPin2, LOW);
		}
		else
		{
			digitalWrite(m_cPin3, LOW);
			digitalWrite(m_cPin4, LOW);
		}
	}
};

/*
CDCMotorDriver g_MotorDriver(MOTOR_PIN1, MOTOR_PIN1, MOTOR_PIN1, MOTOR_PIN1, MOTOR_PWM1, MOTOR_PWM2, true);

void setup()
{
	//반드시 Init을 한번 호출해 줍니다.
	g_MotorDriver.Init();
}

void loop()
{
	//2초동안 두개 모터를 모두 최고 속도로 정회전 제어 합니다.
	g_MotorDriver.ForwardAll(255, 255);
	delay(2000);

	//2초동안 두개 모터를 모두 최고 속도로 역회전 제어 합니다.
	g_MotorDriver.BackwardAll(255, 255);
	delay(2000);

	//1초동안 모든 모터를 정지 시킵니다.
	g_MotorDriver.StopAll();
	delay(1000);

	//1초동안 좌측 모터만 1/2속도로 정회전 시킵니다.
	g_MotorDriver.ForwardLeftMotor(127);
	delay(1000);

	//1초동안 우측 모터만 1/2속도로 정회전 시킵니다.
	g_MotorDriver.StopLeft(); //일단 회전하고 있는 좌측 모터는 정지 시키고
	g_MotorDriver.ForwardRightMotor(127);
	delay(1000);

	//2초동안 좌측은 1/2속도로 정회전, 우측은 최고 속도로 역회전시킵니다.
	g_MotorDriver.ForwardLeftMotor(127);
	g_MotorDriver.BackwardRightMotor(255);
	delay(2000);

}*/
#endif
