/*
	c++ ==> opencv, 간단히 USB 캠의 영상을 출력하는 코드
*/
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int, char**){
	//웹캡으로 부터 데이터 읽어오기 위해 준비
	VideoCapture cap1(1);

	if (!cap1.isOpened()) 
		cout << "첫번째 카메라를 열 수 없습니다." << endl;

	Mat frame1;
	namedWindow("camera1", 1);

	while (1) {
		//웹캡으로부터 한 프레임을 읽어옴
		cap1 >> frame1;
		imshow("camera1", frame1);
		// esc키를 누르면 종료
		if (waitKey(1) == 27) break;
	}

	return 0;
}
