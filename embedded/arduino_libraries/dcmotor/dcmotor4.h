#ifndef DCMOTOR_4_H_
#define DCMOTOR_4_H_

class CDCMotor4WD
{
	uint8_t m_cFrontLeftPwm;
	uint8_t m_cFrontLeftPin;

	uint8_t m_cFrontRightPwm;
	uint8_t m_cFrontRightPin;

	uint8_t m_cBackLeftPwm;
	uint8_t m_cBackLeftPin;

	uint8_t m_cBackRightPwm;
	uint8_t m_cBackRightPin;

public:
	CDCMotor4WD(uint8_t fleftpwm, uint8_t fleftpin, uint8_t frightpwm, uint8_t frightpin, uint8_t bleftpwm, uint8_t bleftpin, uint8_t brightpwm, uint8_t brightpin)
	{
		m_cFrontLeftPwm = fleftpwm;
		m_cFrontLeftPin = fleftpin;

		m_cFrontRightPwm = frightpwm;
		m_cFrontRightPin = frightpin;

		m_cBackLeftPwm = bleftpwm;
		m_cBackLeftPin = bleftpin;

		m_cBackRightPwm = brightpwm;
		m_cBackRightPin = brightpin;
	}

	void Init()
	{
		pinMode(m_cFrontLeftPwm, OUTPUT);
		pinMode(m_cFrontLeftPin, OUTPUT);

		pinMode(m_cFrontRightPwm, OUTPUT);
		pinMode(m_cFrontRightPin, OUTPUT);

		pinMode(m_cBackLeftPwm, OUTPUT);
		pinMode(m_cBackLeftPin, OUTPUT);

		pinMode(m_cBackRightPwm, OUTPUT);
		pinMode(m_cBackRightPin, OUTPUT);

		StopAll();
	}

	void StopAll()
	{
		StopLeftFront();
		StopLeftBack();
		StopRightFront();
		StopRightBack();
	}

	void StopLeftSide()
	{
		StopLeftFront();
		StopLeftBack();
	}

	void StopRightSide()
	{
		StopRightFront();
		StopRightBack();
	}

	void ForwardAll(int speed)
	{
		MoveFront(m_cFrontLeftPwm, m_cFrontLeftPin, speed);
		MoveFront(m_cFrontRightPwm, m_cFrontRightPin, speed);
		MoveFront(m_cBackLeftPwm, m_cBackLeftPin, speed);
		MoveFront(m_cBackRightPwm, m_cBackRightPin, speed);
	}

	void BackwardAll(int speed)
	{
		MoveBack(m_cFrontLeftPwm, m_cFrontLeftPin, speed);
		MoveBack(m_cFrontRightPwm, m_cFrontRightPin, speed);
		MoveBack(m_cBackLeftPwm, m_cBackLeftPin, speed);
		MoveBack(m_cBackRightPwm, m_cBackRightPin, speed);
	}

	void ForwardAll(int leftspeed, int rightspeed)
	{
		MoveFront(m_cFrontLeftPwm, m_cFrontLeftPin, leftspeed);
		MoveFront(m_cFrontRightPwm, m_cFrontRightPin, rightspeed);
		MoveFront(m_cBackLeftPwm, m_cBackLeftPin, leftspeed);
		MoveFront(m_cBackRightPwm, m_cBackRightPin, rightspeed);
	}

	void BackwardAll(int leftspeed, int rightspeed)
	{
		MoveBack(m_cFrontLeftPwm, m_cFrontLeftPin, leftspeed);
		MoveBack(m_cFrontRightPwm, m_cFrontRightPin, rightspeed);
		MoveBack(m_cBackLeftPwm, m_cBackLeftPin, leftspeed);
		MoveBack(m_cBackRightPwm, m_cBackRightPin, rightspeed);
	}

	void TurnLeft(int leftspeed, int rightspeed)
	{
		MoveBack(m_cFrontLeftPwm, m_cFrontLeftPin, leftspeed);
		MoveBack(m_cBackLeftPwm, m_cBackLeftPin, leftspeed);

		MoveFront(m_cFrontRightPwm, m_cFrontRightPin, rightspeed);
		MoveFront(m_cBackRightPwm, m_cBackRightPin, rightspeed);
	}

	void TurnRight(int leftspeed, int rightspeed)
	{
		MoveFront(m_cFrontLeftPwm, m_cFrontLeftPin, leftspeed);
		MoveFront(m_cBackLeftPwm, m_cBackLeftPin, leftspeed);

		MoveBack(m_cFrontRightPwm, m_cFrontRightPin, rightspeed);
		MoveBack(m_cBackRightPwm, m_cBackRightPin, rightspeed);
	}
protected:

	void MoveFront(int pwm, int pin, int speed)
	{
		analogWrite(pwm, speed);
		digitalWrite(pin, LOW);
	}

	void MoveBack(int pwm, int pin, int speed)
	{
		analogWrite(pwm, 255 - speed);
		digitalWrite(pin, HIGH);
	}

	void StopLeftFront()
	{
		digitalWrite(m_cFrontLeftPwm, LOW);
		digitalWrite(m_cFrontLeftPin, LOW);
	}

	void StopRightFront()
	{
		digitalWrite(m_cFrontRightPwm, LOW);
		digitalWrite(m_cFrontRightPin, LOW);
	}

	void StopLeftBack()
	{
		digitalWrite(m_cBackLeftPwm, LOW);
		digitalWrite(m_cBackLeftPin, LOW);
	}

	void StopRightBack()
	{
		digitalWrite(m_cBackRightPwm, LOW);
		digitalWrite(m_cBackRightPin, LOW);
	}
};
#endif