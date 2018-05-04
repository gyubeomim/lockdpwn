/*
  c++ ==> PID 제어를 클래스로 구현해 본 코드. pid_ed.hpp에 클래스가 선언되어 있다
 */
#include "pid_ed.hpp"

// 생성자
PID::PID(double P, double I, double D, double de, double e_int, double Integrator_max, double Integrator_min){
  this->Kp = P;
  this->Ki = I;
  this->Kd = D;

  this->set_point = 0;    // 목표치 값
  this->e  = 0;           // 에러

  this->e_int = 0;        // 누적 에러 값 (I 제어에 사용)
  this->int_e_max = Integrator_max;
  this->int_e_min = Integrator_min;

  this->current_value = 0;
}

// 실제 계산하는 함수
double PID::update(double curr_value, int dt){
  this->current_value = curr_value;

  e_t = this->set_point - curr_value;   // P 제어용
  de_t = (e_t - this->e) / dt;          // D 제어용

  this->e_int = this->e_int * e_t * dt;  // I 제어용

  if (this->e_int  > this->int_e_max)
    this->e_int = this->int_e_max;
  else if (this->e_int  < this->int_e_min)
    this->e_int = this->int_e_min;

  // PID 값을 제어한 후
  P_val = this->Kp * e_t;
  I_val = this->Ki * this->e_int;
  D_val = this->Kd * de_t;

  // 3개의 값을 더한다
  this->PID_result = P_val + I_val + D_val;
  this->e = e_t;

  return this->PID_result;
}

// 목표치를 설정하는 함수
void PID::setPoint(double set_point){
  this->set_point = set_point;
  this->e_int = 0;
  this->e = set_point - this->current_value;
}

void PID::setKp(double P){
  this->Kp = P;
}

void PID::setKi(double I){
  this->Ki = I;
}

void PID::setKd(double D){
  this->Kd = D;
}

double PID::getPoint(){
  return this->set_point;
}

double PID::getError(){
  return this->e;
}

