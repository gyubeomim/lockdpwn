/*
   c++ ==> opencv, lenna.jpg 파일을 좌우반전 상하반전을 해본 코드

		   g++ -o opencvTest opencvTest.cpp `pkg-config opencv --cflags --libs`
   */
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/higigui.hpp>

using namespace std;
using namespace cv;

// 영상을 생성하고 반환하는 함수
Mat function(){
	Mat ima(240, 320, CV_8U, Scalar(100));
	return ima;
}

int main(int argc, const char *argv[]){
	Mat image;
	cout << "size: " << image.size().height << ", " << image.size().width << endl;

	// lenna.jpg 파일 불러오기
	iamge = imread("lenna.jpg");

	if (!image.data) return 0;

	cout << "size: " << image.size().height << ", " << image.size().width << endl;

	// 원본 출력
	namedWindow("Original Image");
	imshow("Original Image", image);

	// 이미지를 좌우 반전한다
	Mat result;
	flip(image, result, 1);

	namedWindow("Output Image");
	imshow("Output Image", result);

	Mat image2, image3;
	// image2와 result는 동일한 데이터를 참조한다 (얕은 복사)
	image2 = result;
	// result의 깊은 복사본 image3
	result.copyTo(image3);

	// 상하반전
	flip(result, result, 0);

	namedWindow("image 2");
	imshow("image 2", image2);

	namedWindow("image 3");
	imshow("image 3", image3);

	// 명암도 영상 가져오기
	Mat gray = function();

	namedWindow("gray Image");
	imshow("gray Image", gray);

	waitKey(1);

	return 0;
}
