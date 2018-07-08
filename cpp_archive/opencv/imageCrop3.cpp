/*
	c++ ==> opencv, hangeulSample.png를 grid를 제거한 후 각각의 한글데이터만 따로 잘라서 저장하는 코드
*/
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, const char *argv[]) {
	// 사진파일을 읽는다
	Mat image = imread("hangeulSample.png");
	if (!image.data) return 0;

	// 이미지 크기를 입력한다
	int horizontal = 55;
	int vertical = 77;
	Mat tile;
	stringstream ss;
	string filename = "";
	int count = 0;

	// rows : 세로 픽셀 길이
	// cols : 가로 픽셀 길이 
	// 이미지를 (horizontal,vertical) 사이즈로 자른다음 image%d.jpg로 반복해서 저장하는 코드
	for (int r = 0; r < image.rows; r += vertical)
		for (int c = 0; c < image.cols; c += horizontal){
			
			// 루프를 돌면서 tile 변수에 grid의 크기만큼 데이터를 잘라서 입력한다
			tile = image(Range(r, min(r + vertical, image.rows)),
				Range(c, min(c + horizontal, image.cols)));

			// 너무 작게 잘리는 이미지들은 skip 한다
			if (tile.rows < vertical - 5 ||  tile.cols < horizontal -5)
				continue;
			
			// 이미지 테두리를 제거한다
			tile = tile(Rect(5,10, 50, 55));
			
			// tile 변수를 바로바로 저장한다
			ss << "cropped_" << (count + 1) << ".jpg";
			count++;
			filename = ss.str();
			ss.str("");
			imwrite(filename, tile);
		}

	waitKey(0);
	return 0;
}

