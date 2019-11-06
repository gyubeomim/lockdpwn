#include <iostream>
#include <Eigen/Dense>

// #define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
// #define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)
//
using namespace std;
using namespace Eigen;

int main() {
	// double a1 = degreesToRadians(30);
	// double a2 = degreesToRadians(30);

	Eigen::Quaterniond q1 = Eigen::AngleAxisd(1.57, Eigen::Vector3d::UnitZ());
	//Eigen::Quaternion<double> q2 = Eigen::AngleAxis<double>(3.14, Eigen::Vector3d(0,0,1));

	cout << q1 << endl;
}
