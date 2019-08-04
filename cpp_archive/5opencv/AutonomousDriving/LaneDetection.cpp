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

const Scalar COLOR_BLUE = Scalar(255, 0, 0);
const Scalar COLOR_RED = Scalar(0, 0, 255);
const float DEGREE1 = CV_PI * 1 / 180;
const float DEGREE90 = CV_PI * 90 / 180;

bool getLeftLines(Mat* originImg, Mat* grayImg, Mat* cannyImg, float* resultLine, double theta) {
  vector<Vec2f> linesL;

  // 왼쪽 차선 검출
  for (int i = 10; i > 0; i--) {
    int threshold = (grayImg->rows + grayImg->cols) * i / 10;
    HoughLines(*cannyImg, linesL, 1, CV_PI / 180, threshold, 0, 0, 0, theta - DEGREE1);
    if (linesL.size() > 0)
    {
      // Theta가 가장 작은 선 1개만 검출
      resultLine[RHO] = linesL[0][0];
      resultLine[THETA] = linesL[0][1];

      for (size_t i = 1; i < linesL.size(); i++)
      {
        if (linesL[i][1] < resultLine[THETA])
        {
          resultLine[RHO] = linesL[i][0];
          resultLine[THETA] = linesL[i][1];
        }
      }
      return true;
    }
  }
  return false;
}

void calLeftLanePoint(Mat* originImg, float* resultLine, Point* leftP) {
  float rho = resultLine[RHO];
  float theta = resultLine[THETA];
  double a = cos(theta), b = sin(theta);
  double x0 = a * rho, y0 = b * rho;

  leftP[0].x = cvRound(x0 + (originImg->rows + originImg->cols) * (-b));
  leftP[0].y = cvRound(y0 + (originImg->rows + originImg->cols) * (a)) + originImg->rows / 2;

  leftP[1].x = cvRound(x0 - (originImg->rows + originImg->cols) * (-b));
  leftP[1].y = cvRound(y0 - (originImg->rows + originImg->cols) * (a)) + originImg->rows / 2;
}

bool getRightLines(Mat* originImg, Mat* grayImg, Mat* cannyImg, float* resultLine, double theta) {
  vector<Vec2f> linesR;

  // 오른쪽 차선 검출
  for (int i = 10; i > 0; i--) {
    int threshold = (grayImg->rows + grayImg->cols) * i / 10;
    HoughLines(*cannyImg, linesR, 1, CV_PI / 180, threshold, 0, 0, theta + DEGREE1, CV_PI);
    if (linesR.size() > 0)
    {
      // Theta가 가장 큰 선 1개만 검출
      resultLine[RHO] = linesR[0][0];
      resultLine[THETA] = linesR[0][1];

      for (size_t i = 1; i < linesR.size(); i++)
      {
        if (linesR[i][1] > resultLine[THETA])
        {
          resultLine[RHO] = linesR[i][0];
          resultLine[THETA] = linesR[i][1];
        }
      }
      return true;
    }
  }
  return false;
}
//
void calRightLanePoint(Mat* originImg, float* resultLine, Point* rightP) {
  float rho = resultLine[RHO];
  float theta = resultLine[THETA];
  double a = cos(theta), b = sin(theta);
  double x0 = a * rho, y0 = b * rho;

  rightP[0].x = cvRound(x0 + (originImg->rows + originImg->cols) * (-b));
  rightP[0].y = cvRound(y0 + (originImg->rows + originImg->cols) * (a)) + originImg->rows / 2;

  rightP[1].x = cvRound(x0 - (originImg->rows + originImg->cols) * (-b));
  rightP[1].y = cvRound(y0 - (originImg->rows + originImg->cols) * (a)) + originImg->rows / 2;
}

int main() {
  namedWindow("Original", CV_WINDOW_AUTOSIZE);
  /* namedWindow("Canny", CV_WINDOW_AUTOSIZE); */

  Mat originImg;
  Mat grayImg;
  Mat cannyImg;
  Mat imageROI;

  Point leftP[2], rightP[2], banishP;

  string fileName = "/home/dyros-vehicle/gitrepo/lockdpwn/cpp_archive/opencv/AutonomousDriving/lane.jpg";

  //IplImage *dstImage;
  //dstImage = cvCreateImage(cvSize(512, 512), IPL_DEPTH_8U, 3);
  originImg = imread(fileName, CV_LOAD_IMAGE_COLOR);
  //cvRectangle(dstImage, cvPoint(100, 100), cvPoint(400, 400), CV_RGB(255, 0, 0));
  /* grayImg = imread(fileName, CV_LOAD_IMAGE_GRAYSCALE); */

  imageROI = grayImg(Rect(0, grayImg.rows/2, grayImg.cols, grayImg.rows/2));
  Canny(imageROI, cannyImg, (grayImg.rows + grayImg.cols)/4, (grayImg.rows + grayImg.cols)/4);

  getLeftLines(&originImg, &grayImg, &cannyImg, resultLine[LEFTLINE], CV_PI/2);
  getRightLines(&originImg, &grayImg, &cannyImg, resultLine[RIGHTLINE], CV_PI/2);

  // 좌우 차선이 이루는 각이 90도 보다 큰 경우 각도가 완만한 차선을 버리고 다시 검출
  while (abs(resultLine[RIGHTLINE][THETA] - resultLine[LEFTLINE][THETA]) < DEGREE90) {
    if (CV_PI/2 - resultLine[LEFTLINE][THETA] <= resultLine[RIGHTLINE][THETA] - CV_PI/2) {
      // 좌측 차선 다시 검출
      getLeftLines(&originImg, &grayImg, &cannyImg, resultLine[LEFTLINE], resultLine[LEFTLINE][THETA]);
    }
    else {
      // 우측 차선 다시 검출
      getRightLines(&originImg, &grayImg, &cannyImg, resultLine[RIGHTLINE], resultLine[RIGHTLINE][THETA]);
    }
  }

  calLeftLanePoint(&originImg, resultLine[LEFTLINE], leftP);
  calRightLanePoint(&originImg, resultLine[RIGHTLINE], rightP);

  /* 소실점 검출 */
  // 왼쪽 차선의 1차 방정식
  float leftLineA = (float)(leftP[1].y - leftP[0].y) / (float)(leftP[1].x - leftP[0].x);
  float leftLineB = leftP[1].y - leftLineA * leftP[1].x;

  // 오른쪽 차선의 1차 방정식
  float rightLineA = (float)(rightP[1].y - rightP[0].y) / (float)(rightP[1].x - rightP[0].x);
  float rightLineB = rightP[1].y - rightLineA * rightP[1].x;

  // 1차 소실점: 좌우 1차선의 교점
  banishP.x = (int)((rightLineB - leftLineB) / (leftLineA - rightLineA));
  banishP.y = (int)(leftLineA * banishP.x + leftLineB);

  line(originImg, leftP[0], banishP, COLOR_BLUE, 2);
  line(originImg, rightP[1], banishP, COLOR_BLUE, 2);

  imshow("Original", originImg);
  /* cv::imshow("Canny", cannyImg); */

  //cvShowImage("Drawing Graphics", dstImage);
  waitKey(0);
  destroyWindow("Original");
  /* destroyWindow("Canny"); */
}
