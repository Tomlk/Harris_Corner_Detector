#pragma once
#include "opencv2/imgproc/imgproc.hpp"    
#include "opencv2/highgui/highgui.hpp"    
#include <iostream>    
using namespace cv;
using namespace std;
class Harris
{
public:
	Harris();
	~Harris();
	void getGrayImg(Mat ImgSource);
	void getSobelIxIy();
	void getMandR(int kernel,double k);// º∆À„Mæÿ’Û∫ÕœÏ”¶R
	void CLocalMaxPoint(int edgelength, int Thresh);//NMS
	void DispResult(Mat sourceImg); //show result 
	Mat getimageSobelX();
	Mat getimageSobelY();
	Mat getDispImg();
	int thresh;
	Mat GaussianImg;
	Mat srcGray;

private:
	Mat ImgSobelX;
	Mat ImgSobelY;
	Mat Operate_SX;
	Mat Operate_SY;
	Mat resultImage;
	Mat PointImage;

	Mat DispImg;
	int Max;
	double Ixx;
	double Iyy;
	double Ixy;
	double R;
	
	


};

