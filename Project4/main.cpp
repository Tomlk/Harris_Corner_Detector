#include  "Harris.h"
#define WINDOW_NAME1 "�����ͼ��"
Harris* harris = new Harris();
const Mat srcImage = imread("test2.jpg");
//***  thresh������ͬͼ��Ҫ����
int default_thresh = 30000;   
int max_thresh = 100000;
//***thresh������ͬͼ��Ҫ����
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
	GaussianBlur(harris->srcGray, harris->GaussianImg, Size(5, 5), 0, 0); //��˹�˲�
	harris->getSobelIxIy();
	harris->getMandR(7, 0.04); //���ں���

	createTrackbar("�����ֵ:", WINDOW_NAME1, &default_thresh, max_thresh, threshold);
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