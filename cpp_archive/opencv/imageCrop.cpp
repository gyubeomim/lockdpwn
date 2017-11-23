/*
	c++ ==> opencv, ga.jpg 한글 '가'의 사진파일에서 맨 위에 한 줄을 따로 잘라내기 한 코드 
*/

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

/// 마우스를 클릭하면 발생하면 콜백함수
void CallBackFunc(int event, int x, int y, int flags, void* userdata){
	if (event == EVENT_LBUTTONDOWN){
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_RBUTTONDOWN)	{
		cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
	else if (event == EVENT_MBUTTONDOWN)	{
		cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
	}
}

int main(int argc, const char *argv[]) {
	Mat image = imread("ga.jpg");
	if (!image.data) return 0;

//	imshow("image", image);

	int i = 80;
	int j = 421;
	int k = 0;

	while(i < 1600) {
		Rect rect(i, j, 235, 227);
		Mat subImage = image(rect);
		imshow((string(k,'a')), subImage);
	
		i += 235;
//		j += 237;
		k++;

		cout << i << endl;
	}
	
	/// 콜백함수를 호출한다
	//set the callback function for any mouse event
	setMouseCallback("image", CallBackFunc, NULL);

	waitKey(0);
	return 0;
}

