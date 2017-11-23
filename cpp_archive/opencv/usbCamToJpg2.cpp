/*
	c++ ==> opencv, 두개의 캠코더로부터 영상을 받아와 둘을 합친 다음 저장하는 코드
*/
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main() {
	Mat img, img2;	// 동영상 파일 재생을 위한 행렬 선언
	VideoCapture cap(0);	    // 캠으로부터 영상을 받아온다 (혹은 1번)
	VideoCapture cap2(0);

	int count = 0;
	char savefile[200];		// 이미지 파일 이름을 200자 이내로 제한하기 위한 char 변수 선언

	while (1) {
		cap >> img;
		cap2 >> img2;

		imshow("image", img);	  // 영상 출력	
		imshow("image2", img2);

		// 두개의 이미지를 합쳐주는 마법의 명령어 :-)
		hconcat(img, img2, img);

		resize(img, img, Size(200, 100), 0, 0, INTER_CUBIC); // 사진으로 저장할 때는 크기를 downsizing해서 저장한다
		sprintf(savefile, "image%d.jpg", count++);
		imwrite(savefile, img);		// img를 파일로 저장한다.

		if (waitKey(100) == 27)  break; // esc를 누르면 종료한다
	}
	return 0;
}
