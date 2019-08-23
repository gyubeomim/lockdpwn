#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <chrono>
#include <ctime>
#include <climits>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <g2o/core/base_unary_edge.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/solvers/dense/linear_solver_dense.h>
#include <g2o/core/robust_kernel.h>
#include <g2o/types/sba/types_six_dof_expmap.h>

using namespace std;
using namespace g2o;

int main(int argc, char **argv) {
  if(argc != 2) {
    cout << "usage: " << endl;
    return 1;
  }

  srand((unsigned int) time(0));
  string path_to_dataset = argv[1];
  string associate_file = path_to_dataset + "/associate.txt";

  ifstream fin(associate_file);

  string rgb_file, depth_file, time_rgb, time_depth;
  cv::Mat color, depth, gray;
  vector<Measurement> measurement;



  return 0;
}
