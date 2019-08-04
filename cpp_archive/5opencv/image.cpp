/*
  c++ ==> opencv, Koala.jpg 사진을 출력하는 코드
*/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {
  cout << "OpenCV Version : " << CV_VERSION << endl;
  Mat img;
  namedWindow("Example1", CV_WINDOW_AUTOSIZE);

  img = imread("./AutonomousDriving/lane.jpg", CV_LOAD_IMAGE_COLOR);
  if (img.empty()) {
    cout << "[!] you can NOT see the picture!" << endl;
    return -1;
  }
  imshow("Example01", img);
  waitKey(0);
  destroyWindow("Example1");

  return 0;
}
