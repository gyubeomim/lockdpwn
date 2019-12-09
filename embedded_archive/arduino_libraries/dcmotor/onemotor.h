#ifndef ONE_MOTOR_H_
#define ONE_MOTOR_H_

class COneMotor
{
	uint8_t m_cPwm;
	uint8_t m_cPin;

public:
	COneMotor(uint8_t pwm, uint8_t pin)
	{
		m_cPwm = pwm;
		m_cPin = pin;
	}

	void Init()
	{
		pinMode(m_cPwm, OUTPUT);
		pinMode(m_cPin, OUTPUT);

		Stop();
	}

	void Stop()
	{
		digitalWrite(m_cPwm, LOW);
		digitalWrite(m_cPin, LOW);
	}

	void Forward(int speed)
	{
		if (speed >= 255)
			digitalWrite(m_cPwm, HIGH);
		else
			analogWrite(m_cPwm, speed);
		digitalWrite(m_cPin, LOW);
	}

	void Backward(int speed)
	{
		if (speed == 255)
			digitalWrite(m_cPwm, LOW);
		else
			analogWrite(m_cPwm, 255 - speed);
		digitalWrite(m_cPin, HIGH);
	}
};
#endif