/*
 * c++ ==> opencv, lenna와 logo 파일을 ROI를 설정한 다음 합쳐보는 코드
 */
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

int main(int argc, const char *argv[]) {
	// 이미지 읽기
	Mat image = imread("lenna.jpg");
	Mat logo = imread("lenna_text.jpg");

	if (!image.data) return 0;
	if (!logo.data) return 0;

	Mat result;
	Mat imageROI;

	// 관심영역 ROI 설정
	imageROI = image(Rect(10, 10, logo.cols, logo.rows));

	// 로고를 영상에 더하기
	// void addWeighted( InputArray src1, double alpha, InputArray src2, double beta, double gamma, OutputArray dst )
	addWeighted(imageROI, 1.0, logo, 0.3, 0., imageROI);

	namedWindow("with logo");
	imshow("with logo", image);

	// 다른 로고 파일 읽기
	image = imread("lenna.jpg");
	logo = imread("lenna_text2.jpg");

	// 로고파일의 잡음을 없애기 위해 이진화를 한다. 어중간한 값들은 전부 0 또는 255가 된다
	threshold(logo, logo, 150, 255, 0);
	imwrite("logo.bmp", logo);

	imageROI = image(Rect(10, 10, logo.cols, logo.rows));
	Mat mask = imread("logo.bmp", 0);

	// 로고를 영상에 깊은복사를 합니다
	logo.copyTo(imageROI, mask);

	namedWindow("with logo2");
	imshow("with logo2", image);

	waitKey(0);
	return 0;
}


