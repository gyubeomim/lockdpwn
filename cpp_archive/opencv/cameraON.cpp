/*
  c++ ==> opencv Test
          컴파일 할 때 g++ -o opencvTest opencvTest.cpp `pkg-config opencv --cflags --libs` 와 같이 해줘야 한다
 */
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int, char**)
{
  //웹캡으로 부터 데이터 읽어오기 위해 준비
  VideoCapture cap1(1);

  if (!cap1.isOpened()){
    cout << "첫번째 카메라를 열수 없습니다." << endl;
  }

  Mat frame1;
  namedWindow("camera1", 1);

  while(1){
    //웹캡으로부터 한 프레임을 읽어옴
    cap1 >> frame1;
    imshow("camera1", frame1);

	// q키를 누르면 종료
    if (waitKey(20) >= 0) break;
  }

  return 0;
}
