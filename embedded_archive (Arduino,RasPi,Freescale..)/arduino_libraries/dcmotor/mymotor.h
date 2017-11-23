#ifndef MYMOTOR_H_
#define MYMOTOR_H_

class CPwmMotor
{
	uint8_t m_btPin1, m_btPin2;
	
public:
	CPwmMotor(int pin1, int pin2)
	{
		m_btPin1 = (uint8_t)pin1;
		m_btPin2 = (uint8_t)pin2;
	}

	void Init()
	{
		pinMode(m_btPin1, OUTPUT);
		pinMode(m_btPin2, OUTPUT);
		StopAll();
	}

	void StopAll()
	{
		digitalWrite(m_btPin1, LOW);
		digitalWrite(m_btPin2, LOW);
	}

	void Stop(bool bFirst)
	{
		digitalWrite(bFirst ? m_btPin1 : m_btPin2, LOW);
	}

	void MoveAll(uint8_t speed)
	{
		analogWrite(m_btPin1, speed);
		analogWrite(m_btPin2, speed);
	}

	void Move(bool bFirst, uint8_t speed)
	{
		analogWrite(bFirst ? m_btPin1 : m_btPin2, speed);
	}
};
#endif