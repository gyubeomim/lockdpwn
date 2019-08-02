#ifndef DCMOTOR_MNG_H
#define DCMOTOR_MNG_H

#include <Arduino.h>

class CDCMotorDriver
{
protected:
	char m_cPin1;
	char m_cPin2;

	char m_cPin3;
	char m_cPin4;

	char m_cPwm1;
	char m_cPwm2;

	unsigned char m_cSpeed;
	unsigned char m_cInnerSpeed;
	unsigned char m_cOuterSpeed;
	bool m_bEnablePWM;

public:
	CDCMotorDriver(int pin1, int pin2, int pin3, int pin4, int pwm1, int pwm2, bool bEnablePWM)
	{
		m_cPin1 = (char)pin1;
		m_cPin2 = (char)pin2;
		m_cPin3 = (char)pin3;
		m_cPin4 = (char)pin4;

		m_cPwm1 = (char)pwm1;
		m_cPwm2 = (char)pwm2;

		m_cInnerSpeed = 255;
		m_cOuterSpeed = 255;
		m_cSpeed = 255;
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

		UpdateSpeed();
		StopAll();
	}

	void SetTurnSpeed(unsigned char inner, unsigned char outer)
	{
		m_cInnerSpeed = inner;
		m_cOuterSpeed = outer;
	}

	void SetSpeed(unsigned char speed)
	{
		m_cSpeed = speed;
	}

	void ForwardAll(unsigned char speed)
	{
		m_cSpeed = speed;
		Forward(true);
		Forward(false);
		UpdateSpeed();
	}

	void SmoothTurn(int left, int right, bool bFront)
	{
		if (bFront)
		{
			Forward(true);
			Forward(false);
		}
		else
		{
			Backward(true);
			Backward(false);
		}

		SetSpeed(m_cPwm1, left);
		SetSpeed(m_cPwm2, right);
	}

	void BackwardAll(unsigned char speed)
	{
		m_cSpeed = speed;
		Backward(true);
		Backward(false);
		UpdateSpeed();
	}

	void Forward(bool bMotor1)
	{
		if (bMotor1)
		{
			CW(m_cPin1, m_cPin2);
		}
		else
		{
			CW(m_cPin3, m_cPin4);
		}
	}

	void Backward(bool bMotor1)
	{
		if (bMotor1)
		{
			CCW(m_cPin1, m_cPin2);
		}
		else
		{
			CCW(m_cPin3, m_cPin4);
		}
	}

	void StopAll()
	{
		Stop(true);
		Stop(false);
	}

	void Stop(bool bMotor1)
	{
		if (bMotor1)
			Stop(m_cPin1, m_cPin2);
		else
			Stop(m_cPin3, m_cPin4);
	}

	void TurlLeft(bool bFront)
	{
		if (bFront)
		{
			Backward(true); 
			Forward(false);

			SetSpeed(m_cPwm1, m_cInnerSpeed);
			SetSpeed(m_cPwm2, m_cOuterSpeed);
		}
		else
		{
			Forward(true);
			Backward(false);

			SetSpeed(m_cPwm1, m_cInnerSpeed);
			SetSpeed(m_cPwm2, m_cOuterSpeed);
		}
	}

	void TurnRight(bool bFront)
	{
		if (bFront)
		{
			Forward(true);
			Backward(false);

			SetSpeed(m_cPwm1, m_cOuterSpeed);
			SetSpeed(m_cPwm2, m_cInnerSpeed);
		}
		else
		{
			Backward(true);
			Forward(false);

			SetSpeed(m_cPwm1, m_cOuterSpeed);
			SetSpeed(m_cPwm2, m_cInnerSpeed);
		}
	}

	void UpdateSpeed()
	{
		SetSpeed(m_cPwm1, m_cSpeed);
		SetSpeed(m_cPwm2, m_cSpeed);
	}

	void UpdateSpeed(bool bFirst, unsigned char speed)
	{
		if (bFirst)
			SetSpeed(m_cPwm1, speed);
		else
			SetSpeed(m_cPwm2, speed);
	}
private:

	void CCW(int pin1, int pin2)
	{
		digitalWrite(pin1, HIGH);
		digitalWrite(pin2, LOW);
	}

	void CW(int pin1, int pin2)
	{
		digitalWrite(pin1, LOW);
		digitalWrite(pin2, HIGH);
	}

	void Stop(int pin1, int pin2)
	{
		digitalWrite(pin1, LOW);
		digitalWrite(pin2, LOW);
	}

	void SetSpeed(int pin, int speed)
	{
		if (speed == 255 || !m_bEnablePWM)
			digitalWrite(pin, HIGH);
		else
			analogWrite(pin, speed);		
	}
};
#endif