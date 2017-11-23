/*
 * c++ ==> opencv, 이미지 픽셀 데이터에 at() 함수를 통해 접근해서 salt를 뿌려본 코드
 */
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

// 사진에 소금같이 흰색점을 뿌려주는 함수
void salt(Mat &image, int n){
	int i, j; 
	for (int k = 0 ; k < n ; k++) {
		i = rand() % image.cols;
		j = rand() % image.rows;

		if (image.channels() == 1){ // 컬러영상인 경우
			image.at<uchar>(j,i) = 255;
		}
		else if(image.channels() == 3){  // 흑백영상인 경우
			image.at<Vec3d>(j,i)[0] = 255;
			image.at<Vec3d>(j,i)[1] = 255;
			image.at<Vec3d>(j,i)[2] = 255;
		}
	}
}

int main(int argc, const char *argv[]){
	// 랜덤시드 생성
	srand(getTickCount());

	// 이미지를 흑백으로 읽는다
	Mat image = imread("lenna.jpg", 0);

	// 3000개의 salt를 뿌린 후 salted.jpg에 저장한다
	salt(image, 3000);
	namedWindow("image");
	imshow("image", image);

	imwrite("salted.jpg", image);
	waitKey(10000);

	return 0;
}
