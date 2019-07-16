/*
  c++ ==> opencv, lenna의 이미지를 불러오는 코드

          g++ -o opencvTest opencvTest.cpp `pkg-config opencv --cflags --libs`
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


int main(int argc, char *argv[]){
  // lenna의 이미지 경로를 설정합니다
  Mat image = imread("lenna.jpg");
  namedWindow("she is lenna");

  // she is lenna! 이름의 창을 생성합니다
  imshow("she is lenna!", image);
  waitKey(50000);

  return 0;
}
