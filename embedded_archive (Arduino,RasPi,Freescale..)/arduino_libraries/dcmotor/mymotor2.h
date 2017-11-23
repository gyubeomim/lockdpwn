#ifndef MYMOTOR_H_
#define MYMOTOR_H_

class CPwmMotor2
{
	uint8_t m_btPin1, m_btPin2;
	uint8_t m_btPin3, m_btPin4;
	
public:
	CPwmMotor2(int pin1, int pin2, int pin3, int pin4)
	{
		m_btPin1 = (uint8_t)pin1;
		m_btPin2 = (uint8_t)pin2;
		
		m_btPin3 = (uint8_t)pin3;
		m_btPin4 = (uint8_t)pin4;
	}

	void Init()
	{
		pinMode(m_btPin1, OUTPUT);
		pinMode(m_btPin2, OUTPUT);
		pinMode(m_btPin3, OUTPUT);
		pinMode(m_btPin4, OUTPUT);
		StopAll();
	}

	void StopAll()
	{
		digitalWrite(m_btPin1, LOW);
		digitalWrite(m_btPin2, LOW);
		digitalWrite(m_btPin3, LOW);
		digitalWrite(m_btPin4, LOW);
	}

	void Stop(bool bFirst)
	{
		if (bFirst)
		{
			digitalWrite(m_btPin1, LOW);
			digitalWrite(m_btPin2, LOW);
		}
		else
		{
			digitalWrite(m_btPin3, LOW);
			digitalWrite(m_btPin4, LOW);
		}
	}

	void Forward(bool bFirst, uint8_t speed)
	{
		if (bFirst)
		{
			if (speed != 255)
				analogWrite(m_btPin1, speed);
			else
				digitalWrite(m_btPin1, HIGH);

			digitalWrite(m_btPin2, LOW);
		}
		else
		{
			if (speed != 255)
				analogWrite(m_btPin3, speed);
			else
				digitalWrite(m_btPin3, HIGH);

			digitalWrite(m_btPin4, LOW);
		}
	}

	void ForwardAll(uint8_t speed)
	{
		if (speed != 255)
			analogWrite(m_btPin1, speed);
		else
			digitalWrite(m_btPin1, HIGH);
		digitalWrite(m_btPin2, LOW);

		if (speed != 255)
			analogWrite(m_btPin3, speed);
		else
			digitalWrite(m_btPin3, HIGH);
		digitalWrite(m_btPin4, LOW);
	}

	void Backward(bool bFirst, uint8_t speed)
	{
		if (bFirst)
		{
			digitalWrite(m_btPin1, LOW);

			if (speed != 255)
				analogWrite(m_btPin2, speed);
			else
				digitalWrite(m_btPin2, HIGH);
		}
		else
		{
			digitalWrite(m_btPin3, LOW);
			if (speed != 255)
				analogWrite(m_btPin4, speed);
			else
				digitalWrite(m_btPin4, HIGH);
		}		
	}

	void BackwardAll(uint8_t speed)
	{
		digitalWrite(m_btPin1, LOW);
		if (speed != 255)
			analogWrite(m_btPin2, speed);
		else
			digitalWrite(m_btPin2, HIGH);

		digitalWrite(m_btPin3, LOW);
		if (speed != 255)
			analogWrite(m_btPin4, speed);
		else
			digitalWrite(m_btPin4, HIGH);
	}

	void TurnLeft(bool bFront)
	{
		Backward(true, 255);
		Forward(false, 255);
	}

	void TurnRight(bool bFront)
	{
		Backward(false, 255);
		Forward(true, 255);
	}

	void SmoothTurn(int left, int right, bool bFront)
	{
		if (bFront)
		{
			if (left == 255)
				digitalWrite(m_btPin1, HIGH);
			else
				analogWrite(m_btPin1, left);

			digitalWrite(m_btPin2, LOW);

			if (right == 255)
				digitalWrite(m_btPin3, HIGH);
			else
				analogWrite(m_btPin3, right);

			digitalWrite(m_btPin4, LOW);
		}
		else
		{
			if (left == 255)
				digitalWrite(m_btPin2, HIGH);
			else
				analogWrite(m_btPin2, left);

			digitalWrite(m_btPin1, LOW);

			if (right == 255)
				digitalWrite(m_btPin4, HIGH);
			else
				analogWrite(m_btPin4, right);

			digitalWrite(m_btPin3, LOW);
		}
	}
};
#endif