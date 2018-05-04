/*
  c++ ==> PID 제어를 클래스화 해본 코드. pid_ed.cpp에 구현되어 있다
 */
class PID {
	double Kp;
	double Ki;
	double Kd;

	double set_point;
	double e;
	double e_int;
	double int_e_max;
	double int_e_min;

	double e_t;
	double de_t;

	double P_val;
	double I_val;
	double D_val;
	double PID_result;

	double current_value;

public:
	PID(double p=2.0, double i=0, double d=0, double de =0, double e_int = 0, double Integrator_max= 500, double Integrator_min = -500);
	double update(double curr_value, int dt);

	void setPoint(double set_point);

	void setKp(double P);
	void setKi(double I);
	void setKd(double D);

	double getPoint();
	double getError();
};

