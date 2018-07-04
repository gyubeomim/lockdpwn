#include <cstdio>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define LEFTLINE  0
#define RIGHTLINE  1

#define RHO   0
#define THETA 1

using namespace std;
using namespace cv;

int main() {
  namedWindow("Original", CV_WINDOW_AUTOSIZE);

  Mat originImg;
  Mat grayImg;
  Mat cannyImg;
  Mat imageROI;

  float resultLine[2][2];
  Point leftP[2], rightP[2], banishP;

  string fileName = "/home/dyros-vehicle/gitrepo/lockdpwn/cpp_archive/opencv/AutonomousDriving/lane.jpg";

  originImg = imread(fileName, CV_LOAD_IMAGE_COLOR);

  imshow("Original", originImg);

  waitKey(0);

  destroyWindow("Original");
}
