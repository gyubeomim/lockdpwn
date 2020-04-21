#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ximgproc.hpp>

#include <iostream>
#include <string>

int main(int argc, char **argv) {
  std::string left_im = std::string(getenv("HOME")) +"/Pictures/keep/200401_dvstereo/left/000000.png";
  std::string right_im = std::string(getenv("HOME")) + "/Pictures/keep/200401_dvstereo/right/000000.png";

  cv::Mat left = cv::imread(left_im, cv::IMREAD_COLOR);
  cv::Mat right = cv::imread(right_im, cv::IMREAD_COLOR);
  cv::Mat concat1;
  cv::hconcat(left, right, concat1);

  cv::Rect roi1, roi2;
  cv::Rect roi3, roi4;
  roi1.x = 640;
  roi1.y = 640;
  roi1.width = 100;
  roi1.height = 100;

  roi2.x = 1920; // 1280 + 640.
  roi2.y = 640;
  roi2.width = 100;
  roi2.height = 100;

  roi3.x = 703;
  roi3.y = 333;
  roi3.width = 36;
  roi3.height = 46;

  roi4.x = 1979;
  roi4.y = 333;
  roi4.width = 36;
  roi4.height = 46;

  cv::rectangle(concat1, roi1, cv::Scalar(0,0,255),3);
  cv::rectangle(concat1, roi2, cv::Scalar(0,0,255),3);
  cv::rectangle(concat1, roi3, cv::Scalar(0,255,0),3);
  cv::rectangle(concat1, roi4, cv::Scalar(0,255,0),3);

  cv::Mat crop1 = left(roi1);
  cv::Mat crop2 = right(roi1);
  cv::Mat concat2;
  cv::hconcat(crop1, crop2, concat2);

  cv::Mat crop3 = left(roi3);
  cv::Mat crop4 = right(roi3);
  cv::Mat concat3;
  cv::hconcat(crop3, crop4, concat3);

  cv::imshow("concat1", concat1);
  cv::imshow("concat2", concat2);
  cv::imshow("concat3", concat3);
  cv::moveWindow("concat2", 0, 1030);
  cv::waitKey(0);

  return 0;
}
