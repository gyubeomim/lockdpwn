#include <iostream>

#include <Eigen/Dense>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/xfeatures2d.hpp"


using namespace std;
using namespace cv;

inline double GetIntensity(const Eigen::Vector2d proj, cv::Mat* image, bool _bilinear=true) {
  if(_bilinear) {
    double u = proj(0);
    double v = proj(1);

    double _u = u - floor(u);
    double _v = v - floor(v);

    unsigned char i00 = image->at<unsigned char>(v, u);
    unsigned char i01 = image->at<unsigned char>(v, u+1);
    unsigned char i10 = image->at<unsigned char>(v+1, u);
    unsigned char i11 = image->at<unsigned char>(v+1, u+1);

    Eigen::Vector2d bilinear_u, bilinear_v;
    bilinear_u << (1-_u), _u;
    bilinear_v << (1-_v), _v;

    Eigen::Matrix2d data_matrix;
    data_matrix << i00, i01, i10, i11;

    return bilinear_v.transpose() * data_matrix * bilinear_u;
  }
  else {
    double u = proj(0);
    double v = proj(1);

    // get intensity in a direct way.
    return image->at<unsigned char>(v, u);
  }
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

  std::cout << (int)GetIntensity(0,0,test_mat, ) << std::endl;
  std::cout << (int)GetIntensity(0,1,test_mat, ) << std::endl;
  std::cout << (int)GetIntensity(0,2,test_mat, ) << std::endl;
  std::cout << (int)GetIntensity(1,0,test_mat, ) << std::endl;
  std::cout << (int)GetIntensity(1,1,test_mat, ) << std::endl;
  std::cout << (int)GetIntensity(1,2,test_mat, ) << std::endl;

  std::cout << std::endl;

  std::cout << BilinearInterpolation(test_mat, Eigen::Vector2d(.5,.5)) << std::endl;

  return 0;
}
