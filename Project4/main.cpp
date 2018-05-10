#include  "Harris.h"
#define WINDOW_NAME1 "【结果图】"
Harris* harris = new Harris();
const Mat srcImage = imread("test2.jpg");
//***  thresh参数不同图需要调整
int default_thresh = 30000;   
int max_thresh = 100000;
//***thresh参数不同图需要调整
void threshold(int, void*);
const int edgel = 5;
int main()
{
	if (!srcImage.data)
	{
		cout << "could not load image\n";
		return -1;
	}
	namedWindow(WINDOW_NAME1);
	harris->getGrayImg(srcImage);
	GaussianBlur(harris->srcGray, harris->GaussianImg, Size(5, 5), 0, 0); //高斯滤波
	harris->getSobelIxIy();
	harris->getMandR(7, 0.04); //窗口函数

	createTrackbar("相对阈值:", WINDOW_NAME1, &default_thresh, max_thresh, threshold);
	imshow("grayImg", harris->srcGray);
	imshow("srcImage", srcImage);
	imshow("ImgSobelX", harris->getimageSobelX());
	imshow("ImgSobelY", harris->getimageSobelY());

	while (waitKey(9) != 27);
	return 0;
}
void threshold(int, void*)
{
	harris->CLocalMaxPoint(edgel, default_thresh);
	harris->DispResult(srcImage);
	imshow(WINDOW_NAME1, harris->getDispImg());
}