#include <iostream>

#include <Eigen/Dense>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/xfeatures2d.hpp"


using namespace std;
using namespace cv;

inline unsigned char GetIntensity(cv::Mat image_, int u, int v) {
  return image_.at<unsigned char>(u,v);
}

inline double BilinearInterpolation(cv::Mat image_, const Eigen::Vector2d proj) {
  double x = proj(0);
  double y = proj(1);
  double _x = x - floor(x);
  double _y = y - floor(y);

  std::cout << _x << ", " << _y << std::endl;
  std::cout << (int)proj(0) << ", " << (int)proj(1) << std::endl;

  unsigned char i00 = image_.at<unsigned char>(x, y);
  unsigned char i01 = image_.at<unsigned char>(x, y+1);
  unsigned char i10 = image_.at<unsigned char>(x+1, y);
  unsigned char i11 = image_.at<unsigned char>(x+1, y+1);

  Eigen::Vector2d bilinear_x, bilinear_y;
  bilinear_x << (1-_x), _x;
  bilinear_y << (1-_y), _y;

  Eigen::Matrix2d data_matrix;
  data_matrix << i00, i01, i10, i11;

  return bilinear_x.transpose() * data_matrix * bilinear_y;
}

int main(int argc, const char* argv[]) {
  cv::Mat test_mat;

  test_mat = (cv::Mat_<unsigned char>(3,4) << 1,2,3,4,5,6,7,8,9,10,11,12);

  std::cout << test_mat << std::endl;
  std::cout << "size: "<<test_mat.size() << std::endl;
  std::cout << "rows: "<<test_mat.rows << std::endl;
  std::cout << "cols: "<<test_mat.cols << std::endl;

  std::cout << (int)test_mat.at<unsigned char>(0,0) << std::endl;
  std::cout << (int)test_mat.at<unsigned char>(0,1) << std::endl;
  std::cout << (int)test_mat.at<unsigned char>(0,2) << std::endl;
  std::cout << (int)test_mat.at<unsigned char>(0,3) << std::endl;

  std::cout << (int)test_mat.at<unsigned char>(1,0) << std::endl;
  std::cout << (int)test_mat.at<unsigned char>(1,1) << std::endl;
  std::cout << (int)test_mat.at<unsigned char>(1,2) << std::endl;
  std::cout << (int)test_mat.at<unsigned char>(1,3) << std::endl;

  std::cout << (int)test_mat.at<unsigned char>(2,0) << std::endl;
  std::cout << (int)test_mat.at<unsigned char>(2,1) << std::endl;
  std::cout << (int)test_mat.at<unsigned char>(2,2) << std::endl;
  std::cout << (int)test_mat.at<unsigned char>(2,3) << std::endl;

  std::cout << std::endl;

  std::cout << (int)GetIntensity(test_mat, 0,0) << std::endl;
  std::cout << (int)GetIntensity(test_mat, 0,1) << std::endl;
  std::cout << (int)GetIntensity(test_mat, 0,2) << std::endl;
  std::cout << (int)GetIntensity(test_mat, 1,0) << std::endl;
  std::cout << (int)GetIntensity(test_mat, 1,1) << std::endl;
  std::cout << (int)GetIntensity(test_mat, 1,2) << std::endl;

  std::cout << std::endl;

  std::cout << BilinearInterpolation(test_mat, Eigen::Vector2d(.5,.5)) << std::endl;

  return 0;
}
