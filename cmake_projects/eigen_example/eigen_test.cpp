#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
   // MatrixXf A = MatrixXf::Random(3, 2);
   // cout << "Here is the matrix A:\n" << A << endl;
   //
   // VectorXf b = VectorXf::Random(3);
   // cout << "Here is the right hand side b:\n" << b << endl;
   //
   Eigen::Matrix<double,4,1> v,w;
	
   int k=0;
   for(int i=0; i<2;i++){
   	for(int j=0;j<2;j++){
		v(i,j) = k;
		w(i*2+j) = k;
		k+=1;
	}
   }
	
   std::cout << v.transpose() << std::endl << std::endl << w.transpose() << std::endl;

   // cout << "The least-squares solution is:\n" << A.bdcSvd(ComputeThinU | ComputeThinV).solve(b) << endl;
}
