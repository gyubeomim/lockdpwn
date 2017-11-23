/*
* c++ ==> opencv, 여러가지 Morphology 연산들을 수행해본 코드
* 					팽창dilate : 대상이 가지는 작은 구멍들을 채울 수 있다. 노이즈성분이 커질 수 있다
* 					침식erode  : 노이즈를 제거할 수 있다. 대상의 영역이 줄어든다
* 					열림 : 침식 --> 팽창 연산을 연이어 2번 실행
* 					닫힘 : 팽창 --> 침식 연산을 연이어 2번 실행
*/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(int argc, const char *argv[]) {
	// 입력 영상 읽기
	cv::Mat image = cv::imread("binary.bmp");
	if (!image.data)	return 0;

	// 영상 띄워 보기
	cv::namedWindow("Image");
	cv::imshow("Image", image);

	// 영상 침식
	cv::Mat eroded;
	cv::erode(image, eroded, cv::Mat());

	// 침식된 영상 띄워 보기
	cv::namedWindow("Eroded Image");
	cv::imshow("Eroded Image", eroded);

	// 영상 팽창
	cv::Mat dilated;
	cv::dilate(image, dilated, cv::Mat());

	// 팽창된 영상을 띄워 보기
	cv::namedWindow("Dilated Image");
	cv::imshow("Dilated Image", dilated);

	// 큰 구조 요소로 영상 침식
	cv::Mat element(7, 7, CV_8U, cv::Scalar(1));
	cv::erode(image, eroded, element);

	// 침식된 영상 띄워 보기
	cv::namedWindow("Eroded Image (7x7)");
	cv::imshow("Eroded Image (7x7)", eroded);

	// 영상을 세 번 침식시키기.
	cv::erode(image, eroded, cv::Mat(), cv::Point(-1, -1), 3);

	// 침식된 영상 띄워 보기
	cv::namedWindow("Eroded Image (3 times)");
	cv::imshow("Eroded Image (3 times)", eroded);

	// 영상 닫힘
	cv::Mat element5(5, 5, CV_8U, cv::Scalar(1));
	cv::Mat closed;
	cv::morphologyEx(image, closed, cv::MORPH_CLOSE, element5);

	// 영상 닫힙 띄워 보기
	cv::namedWindow("Closed Image");
	cv::imshow("Closed Image", closed);

	// 영상 열림
	cv::Mat opened;
	cv::morphologyEx(image, opened, cv::MORPH_OPEN, element5);

	// 영상 열림 띄워 보기
	cv::namedWindow("Opened Image");
	cv::imshow("Opened Image", opened);

	// 영상 닫힘과 영상 열림
	cv::morphologyEx(image, image, cv::MORPH_CLOSE, element5);
	cv::morphologyEx(image, image, cv::MORPH_OPEN, element5);


	// 영상 닫힘/열림 띄워 보기
	cv::namedWindow("Closed and Opened Image");
	cv::imshow("Closed and Opened Image", image);
	cv::imwrite("binaryGroup.bmp", image);


	// 입력 영상 읽기
	image = cv::imread("binary.bmp");


	// 영상 닫힘과 영상 열림
	cv::morphologyEx(image, image, cv::MORPH_OPEN, element5);
	cv::morphologyEx(image, image, cv::MORPH_CLOSE, element5);

	// 영상 닫힘/열림 띄워 보기
	cv::namedWindow("Opened and Closed Image");
	cv::imshow("Opened and Closed Image", image);

	cv::waitKey(0);

	return 0;
}



