#include <iostream>

using namespace std;

typedef struct Params_t {
  double D[9];
  double r1[3];
  double xp[3];
  double Qp[9];
  double r2[3];
  double r3[3];
  double r4[3];
  double r5[3];
  double r6[3];
  double r7[3];
  double r8[3];
  double R2[1];
  double Q[9];
  double A0[9];
  double xtilde_0[3];
  double B0[3];
  double A1[9];
  double B1[3];
  double A2[9];
  double B2[3];
  double A3[9];
  double B3[3];
  double A4[9];
  double B4[3];
  double A5[9];
  double B5[3];
  double A6[9];
  double B6[3];
  double u_max[1];
  double *xtilde[1];
} Params;

int main() {
    Params params;
    double **tmp = new double*[8];
    tmp[0] = params.r1;
    // tmp[1] = params.r2;
    // tmp[2] = params.r3;
    // tmp[3] = params.r4;
	// ...
    // tmp[7] = params.r8;
	
	params.r1[0] = 1;
    params.r1[1] = 2;
    params.r1[2] = 3;

	// ed: output is 1, 2, 3
    cout << tmp[0][0] << ", " << tmp[0][1] << ", " << tmp[0][2] << endl;

	// ed: tmp 값을 바꾸면 pointer의 성질로 인해 params.r1[...]의 값이 바뀌므로 for loop를 돌릴 때 tmp의 2차원 배열을 돌리면 더 편할 것 같습니다
	tmp[0][0] = 4;
	tmp[0][1] = 5;
	tmp[0][2] = 6;

	// ed: output is 4, 5, 6
	cout << params.r1[0] << ", " << params.r1[1] << ", " << params.r1[2] << endl;

    return 0;
}
