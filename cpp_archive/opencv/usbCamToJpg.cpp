/*
	c++ ==> opencv, 웹캠의 영상을 출력함과 동시에 
					1초에 10장의 이미지를 jpg 파일로 사진 사이즈를 줄여서 저장하는 코드
*/
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main() {
	Mat img;				// 동영상 파일 재생을 위한 행렬 선언
	VideoCapture cap(0);	// 캠으로부터 영상을 받아온다 (혹은 1번)

	int count = 0;
	char savefile[200];		// 이미지 파일 이름을 200자 이내로 제한하기 위한 char 변수 선언

	while(1){
		cap >> img;		
		imshow("image", img);	  // 영상 출력	

		resize(img, img, Size(60, 60), 0, 0, INTER_CUBIC);		// 사진으로 저장할 때는 크기를 downsizing해서 저장한다
		sprintf(savefile, "image%d.jpg", count++);
		imwrite(savefile, img);		// img를 파일로 저장한다.

		if (waitKey(100) == 27)  break; // esc를 누르면 종료한다
	}
	return 0;
}
