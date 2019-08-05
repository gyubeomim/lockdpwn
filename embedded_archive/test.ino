#include <MsTimer2.h>
#include <Servo.h>

#define alpha 0.3

Servo myservo;
int n = 0;
int dt = 100;
float rpm = 0;
float LPFvalue = 0;

void getRpm()
{
  rpm = (n * 60) / (dt * 0.002);
  Serial.println(rpm);
  LPFvalue = 0.7*LPFvalue + 0.3*rpm/30.0;
  n = 0;
}

void Encoder()
{
  n += 1;
}

void setup()
{
  Serial.begin(115200);
  attachInterrupt(0, Encoder, CHANGE);
  MsTimer2::set(dt, getRpm);
  MsTimer2::start();

  myservo.attach(9);
}

void loop()
{
  myservo.write(LPFvalue);
}
